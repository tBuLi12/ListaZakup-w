#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include <string>
#include <vector>
#include <unordered_map>
#include "../Product/List.h"
#include <memory>
#include <sstream>

class UI
{
public:
    class Command
    {
    public:
        virtual ~Command() = 0;
        virtual bool exec(std::stringstream&) = 0;
        virtual const char* getHelp() const noexcept = 0;
    };

    class Command_help: public Command
    {
    protected:
        UI* ui;
    public:
        Command_help(UI*);
        virtual bool exec(std::stringstream&);
        virtual const char* getHelp() const noexcept;
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
    void prompt(std::string const& cmdName) const noexcept;
    bool runCommand(std::unique_ptr<Command>& cmd, std::stringstream& args, bool locked=false);

    std::unordered_map<std::string, std::unique_ptr<Command>> commands{};
    std::string selectedCommandName = "";
    std::string promptData;
};


#endif