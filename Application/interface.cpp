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
    parseArgs(argsStrStream, args);
    return (args.size() == 0 || args[0] != "..");
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
        getline(std::cin, commandName);
        args.clear();
        args << commandName;
        args >> commandName;
        auto mapCommand = commands.find(commandName);
        if (mapCommand != commands.end()) {
            while (runCommand(mapCommand->second, args)) {
                prompt();
            }
        } else if (commandName == "quit") {
            exit = true;
        } else {
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

void UI::prompt() const noexcept {
    std::cout << promptData << selectedCommandName <<'>';
}

UI& UI::get() {
    static UI interface;
    return interface;
}


UI::Command::~Command() {};

