#include "listcommadstorage.h"

#include <iostream>

using std::cerr;
using std::endl;

using namespace Bulk;

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

ICommand::WPtr ListCommadStorage::command(uint32_t idx) noexcept
{
    ICommand::WPtr ret;
    try
    {
        ret = m_storage.at(idx);
    }
    catch(std::out_of_range &ex)
    {
        cerr << "Can't get command by index " << idx << ": " << ex.what();
    }

    return ret;
}
