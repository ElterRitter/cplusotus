#pragma once

#include <icommandstorage.h>

#include <vector>

namespace Bulk {

class ListCommadStorage : public ICommandStorage
{
public:
    explicit ListCommadStorage(const uint32_t bulkSize);

    // override members of ICommandStorage
    virtual bool appendCommand( const ICommand::Ptr &cmd ) override final;
    virtual uint32_t bulkSize() const noexcept override final { return m_bulkSize; }
    virtual uint32_t commandsCount() const noexcept override final;
    virtual ICommand::WPtr command(const uint32_t idx) noexcept override final;
    virtual void clear() override final { m_storage.clear(); }

private:
    std::vector<ICommand::Ptr> m_storage;
    uint32_t m_bulkSize;
};

};
