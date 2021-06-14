#include "application.h"
#include "appExceptions.h"
#include <memory>
#include <iostream>

#define NO_LIST "(No list selected)"
#define DEFINE_CMD(name, arg, help) const char* Application::Command_##name::getHelp() const noexcept {return "\e[38;5;4m\e[1m"#name "\e[0m\e[38;5;10m " arg "\e[38;5;15m - " help;} \
        bool Application::Command_##name::exec(std::stringstream& args)

p_count getCount(std::stringstream& args, bool& noCount) {
    p_count count;
    while (std::isspace(args.peek())) {args.get();}
    bool negative = (args.peek() == '-');
    auto pos = args.tellg();
    if (!(args >> count)) {
        args.clear();
        if (count != 0) {
            if (!std::isspace(args.peek())) {
                args.seekg(pos);
            } else {
                throw BadCountException(true);
            } 
        }
        noCount = true;
    } else if (!std::isspace(args.peek())) {
        args.seekg(pos);
    } else if (negative) { throw BadCountException(false); }
    return count;
}

bool getName(std::stringstream& stream, std::string& name) {
    std::string word;
    while (stream >> word) {
        name += word + ' ';
    }
    stream.clear();
    if (name == "") {
        return true;
    }
    name.pop_back();
    return false;
} 



DEFINE_CMD(new, "(list name)", "creates new list named (list name)") {
    std::string listName;
    if (getName(args, listName)) {
        return true;
    }
    if (caller->lists.find(listName) != caller->lists.end()) {
        throw ListExistsException(listName);
    }
    caller->lists[listName] = new List(listName);
    caller->selected = caller->lists[listName];
    caller->interface.setPromptData(listName);
    std::cout << "List " << listName << " created." << std::endl;
    return false;
}


DEFINE_CMD(delete, "", "deletes selected list") {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    caller->lists.erase(caller->selected->get_list_name());
    std::cout << "List " << caller->selected->get_list_name() << " deleted." << std::endl;
    delete caller->selected;
    caller->selected = nullptr;
    caller->interface.setPromptData(NO_LIST);
    return false;
}

DEFINE_CMD(add, "[count] (product name)", "adds product(s) to selected list") {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    bool noCount = false;
    p_count count = getCount(args, noCount);
    std::string productName;
    if (getName(args, productName)) {
        if (noCount) {
            return true;
        }
        throw NotEnoughArgsException(2, 1);
    }
    auto product = caller->products.find(productName);
    if (product == caller->products.end()) {
        throw BadProductException(productName);
    }
    if (noCount) {
        caller->selected->add_product(product->second);
        std::cout << productName << " added." << std::endl;
    } else {
        caller->selected->add_product(product->second, count);
        std::cout << std::to_string(count) << "x " << productName << " added." << std::endl;
    }
    return false;
}

DEFINE_CMD(remove, "(product name)", "removed product from selectes list") {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    std::string productName;
    if (getName(args, productName)) {
        return true;
    }
    auto product = caller->products.find(productName);
    if (product == caller->products.end()) {
        throw BadProductException(productName);
    }
    caller->selected->delete_product(product->second);
    std::cout << productName << " removed." << std::endl;
    return false;
}

DEFINE_CMD(info, "(product name)", "prints info about the product") {
    std::string productName;
    if (getName(args, productName)) {
        return true;
    }
    auto product = caller->products.find(productName);
    if (product == caller->products.end()) {
        throw BadProductException(productName);
    }
    std::cout << product->second->get_info();
    return false;
}

DEFINE_CMD(count, "(count) (product name)", "changes the count of product on selected list") {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    bool noCount = false;
    p_count count = getCount(args, noCount);
    std::string productName;
    if (getName(args, productName) == noCount) {
        if (noCount) {
            return true;
        }
    } else {
        throw NotEnoughArgsException(2, 1);
    }
    auto product = caller->products.find(productName);
    if (product == caller->products.end()) {
        throw BadProductException(productName);
    }
    caller->selected->set_count(product->second, count);
    std::cout << "Count of " << productName << " set to " << count << std::endl;
    return false;
}

DEFINE_CMD(select, "(list name)", "select a list") {
    std::string listName;
    if (getName(args, listName)) {
        return true;
    }
    auto list = caller->lists.find(listName);
    if (list == caller->lists.end()) {
        throw BadListException(listName);
    }
    caller->selected = list->second;
    caller->interface.setPromptData(listName);
    return false;
}

DEFINE_CMD(print, "(list name)", "prints the content of selected list") {
    std::string listName;
    if (getName(args, listName)) {
        if (caller->selected == nullptr) {
            throw NoListSelectedException();
        } else {
            std::cout << *(caller->selected) << std::endl;
        }
        return false;
    }
    auto list = caller->lists.find(listName);
    if (list == caller->lists.end()) {
        throw BadListException(listName);
    } else {
        std::cout << *(list->second) << std::endl;
    }
    return false;
}

DEFINE_CMD(lists, "", "prints all list names") {
    for (auto& listElem: caller->lists) {
        std::cout << listElem.second->get_list_name() << std::endl;
    }
    return false;
}

DEFINE_CMD(products, "", "prints all products") {
    for (auto& listElem: caller->products) {
        std::cout << listElem.second->get_name() << std::endl;
    }
    return false;
}



Application::Application(): interface(UI::get()), parser(*this) {
    interface.setPromptData(NO_LIST);
    #define COMMAND(name) interface.registerCommand(#name, std::unique_ptr<UI::Command>(new Command_##name(this)));
    #include "commands.cmds"
    #undef COMMAND
}

void Application::run() {
    interface.run();
}

Application& Application::get() {
    static Application app;
    return app;
}