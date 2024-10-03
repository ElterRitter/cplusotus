#pragma once
#include "icommand.h"

#include <memory>
#include <inttypes.h>

class ICommandStorage
{
public:
    using Ptr = std::shared_ptr<ICommandStorage>;
    ICommandStorage() = default;
    virtual ~ICommandStorage() = default;

    virtual bool appendCommand(const ICommand::Ptr &cmd) = 0;
    virtual uint32_t bulkSize() const noexcept = 0;
    virtual uint32_t commandsCount() const noexcept = 0;
    virtual ICommand::WPtr command(const uint32_t idx) noexcept = 0;
    virtual void clear() = 0;
};
