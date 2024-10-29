#pragma once
#include "ibulkprinter.h"

namespace Bulk {

/*!
 * \brief Интерфейс IBulkPublisher реализует методы
 */
class IBulkPublisher
{
public:
    IBulkPublisher() = default;
    virtual ~IBulkPublisher() = default;

    /*!
     * \brief Метод subscribePrinter сохраняет "принтеры команд"
     * \param ptrPrinter "принтер", который ожидает блока команд
     */
    virtual void subscribePrinter(const IBulkPrinter::Ptr ptrPrinter) = 0;
    virtual void unsubscribePrinter(const IBulkPrinter::Ptr ptrPrinter) = 0;
};

};  // namespace Bulk
