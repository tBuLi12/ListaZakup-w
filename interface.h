#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER

#include <string>
#include <unordered_map>
#include "Product/List.h"


bool cinEmpty();

class CmdWord
{
private:
    std::string prompt;
    //std::unordered_map<std::string, Command*> actions;
public:
    virtual ~CmdWord() = 0;
    // returns true if the command entered was complete
    virtual bool enter(std::string const& oldPrompt) = 0;
};

class Command: public CmdWord
{
private:
    std::unordered_map<std::string, Command*> actions;
public:
    Command(std::unordered_map<std::string, Command*> actionList)
};

class Agrument: public CmdWord
{

};

class ChoiceMenu: public Command
{
private:
    std::unordered_map<std::string, elemType*> choiceList;
public:
    ChoiceMenu(std::unordered_map<std::string, elemType*> list);
    ~ChoiceMenu();
    bool enter(std::string const& oldPrompt);
};


#endif