#pragma once

#include <ibulkprinter.h>

namespace Bulk {

class BulkPrinterConsole : public IBulkPrinter
{
public:
    BulkPrinterConsole() = default;

    // overrided members of IBulkPrinter
    virtual void processBulk(const ICommandStorage::Ptr ptrBulk) override final;
};

};  // namespace bulk
