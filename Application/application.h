#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "interface.h"
#include "../Product/List.h"
#include "../Product/Product.h"
#include "FileParser.h"
#include <unordered_map>
#include <string>


class Application
{
private:
    class AppCommand: public UI::Command
    {
    protected:
        Application* caller;
    public:
        AppCommand(Application* app): caller(app) {};
    };

    #define COMMAND(name, hasArgs) \
    class name: public AppCommand\
    {\
    public:\
        name(Application* app): AppCommand(app) {};\
        void exec(std::vector<std::string> args);\
        bool takesArgs() const noexcept { return hasArgs; }\
    };
    #include "commands.cmds"
    #undef COMMAND

    List* selected = nullptr;
    UI& interface;
    FileParser parser;
    std::unordered_map<std::string, Product*> products;
    std::unordered_map<std::string, List*> lists;
    Application();
public:
    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;
    static Application& get();
    void run();
};

#endif