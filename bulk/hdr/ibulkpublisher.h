#pragma once
#include "ibulkprinter.h"

class IBulkPublisher
{
public:
    IBulkPublisher() = default;
    virtual ~IBulkPublisher() = default;

    virtual void subscribePrinter(const IBulkPrinter::Ptr ptrPrinter) = 0;
    virtual void unsubscribePrinter(const IBulkPrinter::Ptr ptrPrinter) = 0;
};
