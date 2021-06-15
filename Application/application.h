#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "interface.h"
#include "../Product/List.h"
#include "../Product/Product.h"
#include "FileParser.h"
#include "stack.h"
#include <unordered_map>
#include <string>
#include <sstream>


class Application
{
private:
    #define COMMAND(name) \
    class Command_##name: public UI::Command\
    {\
    protected:\
        Application& caller;\
    public:\
        Command_##name(Application& app): caller(app) {};\
        bool exec(std::stringstream& args);\
        const char* getHelp() const noexcept;\
    };
    #include "commands.cmds"
    #undef COMMAND

    List* selected = nullptr;
    UI& interface;
    Stack<std::string> logs;
    void readFromFiles();
    void writeToFiles();
    std::unordered_map<std::string, Product*> products;
    std::unordered_map<std::string, List*> lists;
    Application();

    friend class ::FileParser;
public:
    ~Application();
    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;
    static Application& get();
    void run();
    void saveLogs();
    FileParser parser;
};

#endif