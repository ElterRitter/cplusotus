#pragma once
#include "icommandstorage.h"
#include "ibulkpublisher.h"

#include <memory>
#include <string>
#include <vector>
#include <stack>

class CommandProcessor : IBulkPublisher
{
public:
    explicit CommandProcessor(uint32_t bulkSize);
    virtual ~CommandProcessor();

    // override members of IBulkPublisher
    void subscribePrinter(const IBulkPrinter::Ptr ptrPrinter) override final;
    void unsubscribePrinter(const IBulkPrinter::Ptr ptrPrinter) override final;

    void processingCommand(const std::string &cmd);
    void finalize();

private:
    std::stack<ICommandStorage::Ptr> m_storages;
    std::vector<IBulkPrinter::Ptr> m_printers;

    void publishBulk();
};
