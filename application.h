#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "interface.h"
#include "Product/List.h"
#include "Product/Product.h"
#include <unordered_map>
#include <string>

class Application
{
private:
    #define COMMAND(name, hasArgs) \
    class name: public UI::Command\
    {\
    public:\
        void exec(std::vector<std::string> args);\
        bool takesArgs() { return hasArgs; }\
    };
    #include "commands.cmds"
    #undef COMMAND

    std::string listName = "(No list selected)";
    UI interface;
    void readFromFiles();
    void writeToFiles();
    std::unordered_map<std::string, Product*> products;
    std::unordered_map<std::string, List> lists;
public:
    void run();
    Application();
};

#endif