#include "commandprocessor.h"
#include "listcommadstorage.h"
#include "commandfabric.h"

#include <limits>

using namespace Bulknet;

CommandProcessor::CommandProcessor(uint32_t bulkSize)
{
    m_storages.push(std::make_shared<ListCommadStorage>(bulkSize));
}

CommandProcessor::~CommandProcessor()
{
    while(m_storages.size() != 0)
        m_storages.pop();
}

void CommandProcessor::processingCommand(const std::string &cmd)
{
    auto command = CommandFabric::instance()->makeCommand(cmd);
    if(!command)
        return;

    switch(command->type())
    {
    case ICommand::Type::common:
        if(!m_storages.top()->appendCommand(command)) {
            publishBulk(m_storages.top()->clone());
        }
        break;
    case ICommand::Type::dynBlockClose:
        if(m_storages.size() == 2)
            publishBulk(m_storages.top());
        if(m_storages.size() > 1)
            m_storages.pop();
        break;
    case ICommand::Type::dynBlockOpen:
        if(m_storages.size() == 1)
        {
            auto storage = std::make_shared<ListCommadStorage>(std::numeric_limits<uint32_t>::max());
            m_storages.push(storage);
        }
        else
        {
            m_storages.push(m_storages.top());
        }
        break;
    }
}

void CommandProcessor::finalize()
{
    if(m_storages.size() == 1)
        publishBulk(m_storages.top());
}

