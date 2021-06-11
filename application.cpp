#include "application.h"
#include "interface.h"
#include <memory>
#include <iostream>
#define DEFINE_CMD(name) void Application::name::exec(std::vector<std::string> args) 

DEFINE_CMD(NewList) {
    std::cout << "newListCalled" << std::endl; 
}

DEFINE_CMD(DeleteList) {
    std::cout << "deleteListCalled" << std::endl;
}

DEFINE_CMD(Add) {
    std::cout << "AddCalled" << std::endl;
}

Application::Application(): interface(listName) {
    #define COMMAND(name, hasArgs) interface.registerCommand(#name, std::unique_ptr<UI::Command>(new name));
    #include "commands.cmds"
    #undef COMMAND
}

void Application::run() {
    interface.run();
}