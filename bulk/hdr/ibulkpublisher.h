#pragma once
#include "ibulkprinter.h"

namespace Bulk {

class IBulkPublisher
{
public:
    IBulkPublisher() = default;
    virtual ~IBulkPublisher() = default;

    virtual void subscribePrinter(const IBulkPrinter::Ptr ptrPrinter) = 0;
    virtual void unsubscribePrinter(const IBulkPrinter::Ptr ptrPrinter) = 0;
};

};  // namespace Bulk
