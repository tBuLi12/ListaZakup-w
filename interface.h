#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include <string>
#include <vector>
#include <unordered_map>
#include "Product/List.h"
#include <memory>

class UI
{
public:
    class Command
    {
    public:
        virtual ~Command() = 0;
        virtual bool takesArgs() = 0;
        virtual void exec(std::vector<std::string>) = 0;
    };

    UI(std::string& listName);
    void registerCommand(std::string name, std::unique_ptr<Command>&& command);
    void run();
private:
    //std::string getCommand(std::vector<std::string>& args);
    //bool getArgs(std::vector<std::string>& args);
    void prompt();

    std::unordered_map<std::string, std::unique_ptr<Command>> commands{};
    std::string selectedCommandName = "";
    std::string& selectedListName;
};


#endif