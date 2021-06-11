#include "interface.h"
#include "listExceptions.h"
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

UI::UI(List* const& listPtr): selectedList(listPtr) {};

void UI::registerCommand(std::string name, std::unique_ptr<Command>&& command) {
    this->commands[name] = std::move(command);
}

void UI::run() {
    std::vector<std::string> args;
    std::string commandName;
    bool exit = false;
    while (!exit) {
        prompt();
        commandName = getCommand(args);
        auto mapCommand = commands.find(commandName);
        if (mapCommand != commands.end()) {
            if (mapCommand->second->takesArgs() && args.size() == 0) {
                selectedCommandName = commandName;
                prompt();
                while (getArgs(args)) {
                    runCommand(mapCommand->second, args);
                    prompt();
                }
                selectedCommandName = "";
            } else {
                runCommand(mapCommand->second, args);
            }
        } else if (commandName == "quit") {
            exit = true;
        } else {
            std::cout << "unknown command: " << commandName << std::endl;
        }
    }
}

void UI::runCommand(std::unique_ptr<Command>& cmd, std::vector<std::string> args) {
    try {
        cmd->exec(args);
    }
    catch (ListException& exception) {
        std::cout << exception.what() << std::endl;
    }
    catch (std::invalid_argument& exception) {
        std::cout << "count argument must be a positive integer" << std::endl;
    }
}


void UI::prompt() {
    std::cout << ((selectedList == nullptr)?"(No list selected)":selectedList->get_list_name()) << selectedCommandName <<'>';
}


UI::Command::~Command() {};

