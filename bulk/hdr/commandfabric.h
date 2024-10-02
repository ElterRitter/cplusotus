#pragma once

#include "icommand.h"

#include <string>

class CommandFabric
{
public:
    static CommandFabric* instance();
    ICommand::Ptr makeCommand(const std::string &data) const;

private:
    CommandFabric() = default;
};

