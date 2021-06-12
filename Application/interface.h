#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include <string>
#include <vector>
#include <unordered_map>
#include "../Product/List.h"
#include <memory>

class UI
{
public:
    class Command
    {
    public:
        virtual ~Command() = 0;
        virtual bool takesArgs() const noexcept = 0;
        virtual void exec(std::vector<std::string>) = 0;
    };
    
    UI(UI const&) = delete;
    UI& operator=(UI const&) = delete;
    void registerCommand(std::string name, std::unique_ptr<Command>&& command);
    void setPromptData(std::string const& data);
    void run();
    static UI& get();
private:
    UI();
    //std::string getCommand(std::vector<std::string>& args);
    //bool getArgs(std::vector<std::string>& args);
    void prompt() const noexcept;
    void runCommand(std::unique_ptr<Command>& cmd, std::vector<std::string> args);

    std::unordered_map<std::string, std::unique_ptr<Command>> commands{};
    std::string selectedCommandName = "";
    std::string promptData;
};


#endif