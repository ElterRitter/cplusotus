#pragma once

#include <ibulkprinter.h>

namespace Bulk {

/*!
 * \brief Класс BulkPrinterConsole являтся реализацией интерфейса IBulkPrinter,
 * который осуществляет вывод накопленных команд в консоль ( cout ).
 */

class BulkPrinterConsole : public IBulkPrinter
{
public:
    BulkPrinterConsole() = default;

    // overrided members of IBulkPrinter
    virtual void processBulk(const ICommandStorage::Ptr ptrBulk) override final;
};

};  // namespace bulk
