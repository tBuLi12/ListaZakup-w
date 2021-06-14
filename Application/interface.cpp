#include "interface.h"
#include "appExceptions.h"
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


std::string getCommand(std::stringstream& args) {
    std::string temp;
    getline(std::cin, temp);
    args.clear();
    args.str(temp);
    temp.clear();
    args >> temp;
    return temp;
}

bool getArgs(std::stringstream& args) {
    std::string temp;
    getline(std::cin, temp);
    if (temp == "..") {
        return false;
    }
    args.clear();
    args.str(temp);
    return true;
}

UI::UI() {};

void UI::registerCommand(std::string name, std::unique_ptr<Command>&& command) {
    this->commands[name] = std::move(command);
}

void UI::run() {
    std::stringstream args;
    std::string commandName;
    bool exit = false;
    while (!exit) {
        prompt();
        commandName = getCommand(args);
        auto mapCommand = commands.find(commandName);
        if (mapCommand != commands.end()) {
            if (runCommand(mapCommand->second, args)) {
                prompt(mapCommand->first);
                while(getArgs(args)) {
                    runCommand(mapCommand->second, args);
                    prompt(mapCommand->first);
                }
            }
        } else if (commandName == "quit") {
            exit = true;
        } else if (commandName != "") {
            std::cout << "unknown command: " << commandName << std::endl;
        }
    }
}

bool UI::runCommand(std::unique_ptr<Command>& cmd, std::stringstream& args) {
    try {
        return cmd->exec(args);
    }
    catch (AppException& exception) {
        std::cout << exception.what() << std::endl;
        return false;
    }
    catch (std::invalid_argument& exception) {
        std::cout << "count argument must be a positive integer" << std::endl;
        return false;
    }
}

void UI::setPromptData(std::string const& data) {
    promptData = data;
}

void UI::prompt(std::string const& cmdName) const noexcept {
    std::cout << promptData << " - " << cmdName <<" > ";
}

void UI::prompt() const noexcept {
    std::cout << promptData <<" > ";
}

UI& UI::get() {
    static UI interface;
    return interface;
}


UI::Command::~Command() {};

