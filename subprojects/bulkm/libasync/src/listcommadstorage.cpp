#include "listcommadstorage.h"

#include <iostream>

using std::cerr;
using std::endl;

using namespace Bulkm;

ListCommadStorage::ListCommadStorage(const std::size_t bulkSize) :
    m_bulkSize{bulkSize}
{

}

// ListCommadStorage::~ListCommadStorage()
// {
//     std::cout << "Destructor of ListCommandStorage with command count " << m_storage.size() << " and bulk size " << m_bulkSize;
// }

bool ListCommadStorage::appendCommand(const ICommand::Ptr &cmd)
{
    auto sz = m_storage.size();
    if(sz > m_bulkSize)
        return false;

    m_storage.emplace_back(cmd);
    return sz+1 != m_bulkSize;
}

std::size_t ListCommadStorage::commandsCount() const noexcept
{
    return m_storage.size();
}

ICommand::WPtr ListCommadStorage::command(const size_t idx) noexcept
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

ICommandStorage::Ptr ListCommadStorage::clone()
{
    auto ret = std::make_shared<ListCommadStorage>(m_bulkSize);
    ret->m_storage.swap(m_storage);
    return ret;
}
