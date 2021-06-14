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

UI::UI() {
    registerCommand("help", std::unique_ptr<UI::Command>(new Command_help(this)));
};

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
                    runCommand(mapCommand->second, args, true);
                    prompt(mapCommand->first);
                }
            }
        } else if (commandName == "quit") {
            exit = true;
        } else if (commandName != "") {
            std::cout << "unknown command: " << commandName << std::endl << "Type \"help\" for valid commands" << std::endl;
        }
    }
}

bool UI::runCommand(std::unique_ptr<Command>& cmd, std::stringstream& args, bool locked) {
    try {
        return cmd->exec(args);
    }
    catch (AppException& exception) {
        std::cout << "\e[38;5;1m\e[1m" << exception.what() << "\e[38;5;15m\e[0m" << std::endl;
        if (locked) { 
            std::cout << "Type \"..\" to leave command" << std::endl;
        }
        return false;
    }
}

void UI::setPromptData(std::string const& data) {
    promptData = data;
}

void UI::prompt(std::string const& cmdName) const noexcept {
    std::cout << "\e[38;5;3m\e[1m" <<promptData << "\e[38;5;10m - " << cmdName <<"\e[38;5;14m > \e[38;5;15m\e[0m";
}

void UI::prompt() const noexcept {
    std::cout << "\e[38;5;3m\e[1m" << promptData <<"\e[38;5;14m > \e[38;5;15m\e[0m";
}

UI& UI::get() {
    static UI interface;
    return interface;
}

UI::Command_help::Command_help(UI* ui): ui(ui) {};

bool UI::Command_help::exec(std::stringstream& args) {
    std::string cmdName;
    args >> cmdName;
    args.clear();
    auto cmd = ui->commands.find(cmdName);
    if (cmd == ui->commands.end()) {
        for (auto& command: ui->commands) {
            std::cout << command.second->getHelp() << std::endl << std::endl;
        }
        std::cout << "\e[38;5;4m\e[1m..\e[38;5;0m\e[0m - leaves command" << std::endl << std::endl;
        std::cout << "\e[38;5;4m\e[1mquit\e[38;5;0m\e[0m - exits the program" << std::endl;
    } else {
        std::cout << cmd->second->getHelp() << std::endl;
    }
    return false;
}

const char* UI::Command_help::getHelp() const noexcept {
    return "\e[38;5;4m\e[1mhelp \e[0m\e[38;5;10m[command name]\e[0m\e[38;5;15m - prints help for all/given command";
}

UI::Command::~Command() {};

