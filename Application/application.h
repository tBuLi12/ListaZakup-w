#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "interface.h"
#include "../Product/List.h"
#include "../Product/Product.h"
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
        bool takesArgs() { return hasArgs; }\
    };
    #include "commands.cmds"
    #undef COMMAND

    List* selected = nullptr;
    UI interface;
    void readFromFiles();
    void writeToFiles();
    std::unordered_map<std::string, Product*> products;
    std::unordered_map<std::string, List*> lists;
public:
    void run();
    Application();
};

#endif