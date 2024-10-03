#include "commandprocessor.h"
#include "listcommadstorage.h"
#include "commandfabric.h"

#include <algorithm>
#include <limits>

using namespace Bulk;

CommandProcessor::CommandProcessor(uint32_t bulkSize)
{
    m_storages.push(std::make_shared<ListCommadStorage>(bulkSize));
}

CommandProcessor::~CommandProcessor()
{
    while(m_storages.size() != 0)
        m_storages.pop();
}

void CommandProcessor::subscribePrinter(const IBulkPrinter::Ptr ptrPrinter)
{
    m_printers.emplace_back(ptrPrinter);
}

void CommandProcessor::unsubscribePrinter(const IBulkPrinter::Ptr ptrPrinter)
{
    auto it = std::find_if(m_printers.begin(), m_printers.end(),
                           [ptrPrinter](const IBulkPrinter::Ptr &item) { return ptrPrinter == item; } );
    if(it != m_printers.end())
        m_printers.erase(it);
}

void CommandProcessor::processingCommand(const std::string &cmd)
{
    auto command = CommandFabric::instance()->makeCommand(cmd);
    if(!command)
        return;

    switch(command->type())
    {
    case ICommand::Type::common:
        if(!m_storages.top()->appendCommand(command))
            publishBulk();
        break;
    case ICommand::Type::dynBlockClose:
        if(m_storages.size() == 2)
            publishBulk();

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
        publishBulk();
}

void CommandProcessor::publishBulk()
{
    for(const auto &printer : m_printers)
        printer->processBulk(m_storages.top());

    m_storages.top()->clear();
}

