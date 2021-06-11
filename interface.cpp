#include "interface.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void parseArgs(std::stringstream& argsStrStream, std::vector<std::string>& args) {
    args.clear();
    std::string argument;
    argsStrStream >> argument;
    while (argument != "") {
        args.push_back(std::move(argument));
        argsStrStream >> argument;
    }
}


std::string getCommand(std::vector<std::string>& args) {
    std::string temp;
    getline(std::cin, temp);
    std::stringstream argsStrStream(temp);
    argsStrStream >> temp;
    parseArgs(argsStrStream, args);
    return temp;
}

bool getArgs(std::vector<std::string>& args) {
    std::string temp;
    getline(std::cin, temp);
    std::stringstream argsStrStream(temp);
    return false;
}

UI::UI(std::string& listName): selectedListName(listName) {};

void UI::registerCommand(std::string name, std::unique_ptr<Command>&& command) {
    this->commands[name] = std::move(command);
}

void UI::run() {
    std::vector<std::string> args;
    std::string commandName;
    while (true) {
        prompt();
        commandName = getCommand(args);
        auto mapCommand = commands.find(commandName);
        if (mapCommand != commands.end()) {
            if (mapCommand->second->takesArgs() && args.size() == 0) {
                //while (getArgs(args)) {
                //    mapCommand->second->exec(args);    
                //}
            } else {
                mapCommand->second->exec(args);
            }
        } else if (commandName == "quit") {
            return;
        } else {
            std::cout << "unknown command: " << commandName << std::endl;
        }
    }
}

void UI::prompt() {
    std::cout << selectedListName << '>';
}

UI::Command::~Command() {};

