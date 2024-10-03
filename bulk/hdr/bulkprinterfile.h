#pragma once

#include <ibulkprinter.h>
#include <string>

namespace Bulk {

class BulkPrinterFile : public IBulkPrinter
{
public:
    explicit BulkPrinterFile(const std::string &rootFolder);

    // overrided members of IBulkPrinter
    virtual void processBulk(ICommandStorage::Ptr ptrBulk) override final;

private:
    std::string m_rootFilder;

    std::string makeFileName(const ICommand::WPtr &cmd);
};

}; // namespace
