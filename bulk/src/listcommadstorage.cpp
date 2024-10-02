#include "listcommadstorage.h"

ListCommadStorage::ListCommadStorage(const uint32_t bulkSize) :
    m_bulkSize{bulkSize}
{

}

bool ListCommadStorage::appendCommand(const ICommand::Ptr &cmd)
{
    auto sz = m_storage.size();
    if(sz > m_bulkSize)
        return false;

    m_storage.emplace_back(cmd);
    return sz+1 != m_bulkSize;
}

uint32_t ListCommadStorage::commandsCount() const noexcept
{
    return m_storage.size();
}

ICommand::Ptr ListCommadStorage::command(uint32_t idx) noexcept
{
    return  m_storage[idx];
}
