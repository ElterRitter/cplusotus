#include "commandfabric.h"

#include "command.h"

CommandFabric *CommandFabric::instance()
{
    static CommandFabric fabric;
    return &fabric;
}

ICommand::Ptr CommandFabric::makeCommand(const std::string &data) const
{
    ICommand::Ptr ret;

    if(data == "{")
        ret = std::make_shared<DynBlockOpenCommand>();
    else if(data == "}")
        ret = std::make_shared<DynBlockCloseCommand>();
    else
        ret = std::make_shared<CommonCommand>(data);

    return ret;
}

