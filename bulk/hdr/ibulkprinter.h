#pragma once
#include "icommandstorage.h"

#include <memory>

class IBulkPrinter
{
public:
    using Ptr = std::shared_ptr<IBulkPrinter>;
    IBulkPrinter() = default;
    virtual ~IBulkPrinter() = default;

    virtual void processBulk(const ICommandStorage::Ptr ptrBulk) = 0;
};
