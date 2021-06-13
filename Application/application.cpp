#include "application.h"
#include "appExceptions.h"
#include <memory>
#include <iostream>

#define NO_LIST "(No list selected)"
#define DEFINE_CMD(name) bool Application::Command_##name::exec(std::stringstream& args) 

p_count strToCount(std::string const& str) {
    unsigned long lCount = std::stoul(str);
    p_count count = lCount;
    if (count != lCount) {
        throw std::out_of_range("count argument too large");
    }
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

DEFINE_CMD(NewList) {
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

DEFINE_CMD(DeleteList) {
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

DEFINE_CMD(Add) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    bool noCount = false;
    p_count count;
    if (!(args >> count)) {
        args.clear();
        noCount = true;
    }
    std::string productName;
    if (getName(args, productName)) {
        if (noCount) {
            return true;
        }
        throw NotEnoughArgsException(1, 2);
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
        std::cout << std::to_string(count) << '*' << productName << " added." << std::endl;
    }
    return false;
}

DEFINE_CMD(Remove) {
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

DEFINE_CMD(Info) {
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

DEFINE_CMD(Count) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    bool noCount;
    p_count count;
    if (!(args >> count)) {
        args.clear();
        noCount = true;
    }
    std::string productName;
    if (getName(args, productName) == noCount) {
        if (noCount) {
            return true;
        }
    } else {
        throw NotEnoughArgsException(1, 2);
    }
    auto product = caller->products.find(productName);
    if (product == caller->products.end()) {
        throw BadProductException(productName);
    }
    caller->selected->set_count(product->second, count);
    std::cout << "Count of " << productName << " set to " << count << std::endl;
    return false;
}

DEFINE_CMD(Select) {
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

DEFINE_CMD(Print) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    std::cout << (*(caller->selected)) << std::endl;
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