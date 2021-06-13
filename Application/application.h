#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "interface.h"
#include "../Product/List.h"
#include "../Product/Product.h"
#include "FileParser.h"
#include <unordered_map>
#include <string>
#include <sstream>


class Application
{
public:
    class AppCommand: public UI::Command
    {
    protected:
        Application* caller;
    public:
        AppCommand(Application* app): caller(app) {};
    };

    #define COMMAND(name) \
    class Command_##name: public AppCommand\
    {\
    public:\
        Command_##name(Application* app): AppCommand(app) {};\
        bool exec(std::stringstream& args);\
    };
    #include "commands.cmds"
    #undef COMMAND

    List* selected = nullptr;
    UI& interface;
    FileParser parser;
    void readFromFiles();
    void writeToFiles();
    std::unordered_map<std::string, Product*> products;
    std::unordered_map<std::string, List*> lists;
    Application();

    //friend class ::FileParser;
public:
    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;
    static Application& get();
    void run();
};

#endif