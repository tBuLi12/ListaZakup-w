#include "application.h"
#include "appExceptions.h"
#include <memory>
#include <iostream>

#define NO_LIST "(No list selected)"
#define DEFINE_CMD(name) void Application::name::exec(std::vector<std::string> args) 

p_count strToCount(std::string const& str) {
    unsigned long lCount = std::stoul(str);
    p_count count = lCount;
    if (count != lCount) {
        throw std::out_of_range("count argument too large");
    }
    return count;
}

DEFINE_CMD(NewList) {
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    if (caller->lists.find(args[0]) != caller->lists.end()) {
        throw ListExistsException(args[0]);
    }
    caller->lists[args[0]] = new List(args[0]);
    caller->selected = caller->lists[args[0]];
    caller->interface.setPromptData(args[0]);
    std::cout << "List " << args[0] << " created." << std::endl;
}

DEFINE_CMD(DeleteList) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    caller->lists.erase(caller->selected->get_list_name());
    std::cout << "List " << caller->selected->get_list_name() << " deleted." << std::endl;
    delete caller->selected;
    caller->selected = nullptr;
}

DEFINE_CMD(Add) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    if (args.size() > 1) {
        caller->selected->add_product(product->second, strToCount(args[1]));
        std::cout << args[1] << '*' << args[0] << " added." << std::endl;
    } else {
        caller->selected->add_product(product->second);
        std::cout << args[0] << " added." << std::endl;
    }
}

DEFINE_CMD(Remove) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    caller->selected->delete_product(product->second);
    caller->interface.setPromptData(NO_LIST);
    std::cout << args[0] << " removed." << std::endl;
}

DEFINE_CMD(Info) {
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    std::cout << product->second->get_info();
}

DEFINE_CMD(Count) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    if (args.size() < 2) {
        throw NotEnoughArgsException(2, args.size());
    }
    auto product = caller->products.find(args[0]);
    if (product == caller->products.end()) {
        throw BadProductException(args[0]);
    }
    caller->selected->set_count(product->second, strToCount(args[1]));
    std::cout << "Count of " << args[0] << " set to " << args[1] << std::endl;
}

DEFINE_CMD(Select) {
    if (args.size() < 1) {
        throw NotEnoughArgsException(1, args.size());
    }
    auto list = caller->lists.find(args[0]);
    if (list == caller->lists.end()) {
        throw BadListException(args[0]);
    }
    caller->selected = list->second;
    caller->interface.setPromptData(args[0]);
}

DEFINE_CMD(Print) {
    if (caller->selected == nullptr) {
        throw NoListSelectedException();
    }
    //std::cout << (*(caller->selected)) << std::endl;
}

Application::Application(): interface(UI::get()) {
    parser = FileParser(products, lists);
    interface.setPromptData(NO_LIST);
    #define COMMAND(name, hasArgs) interface.registerCommand(#name, std::unique_ptr<UI::Command>(new name(this)));
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