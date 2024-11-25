#include "commandfabric.h"

#include "command.h"

using namespace Bulknet;

constexpr auto predefinedCommandDynBlockOpen = "{";
constexpr auto predefinedCommandDynBlockClose = "}";

CommandFabric *CommandFabric::instance()
{
    static CommandFabric fabric;
    return &fabric;
}

ICommand::Ptr CommandFabric::makeCommand(const std::string &data) const
{
    ICommand::Ptr ret;

    if(data == predefinedCommandDynBlockOpen)
        ret = std::make_shared<DynBlockOpenCommand>();
    else if(data == predefinedCommandDynBlockClose)
        ret = std::make_shared<DynBlockCloseCommand>();
    else
        ret = std::make_shared<CommonCommand>(data);

    return ret;
}

