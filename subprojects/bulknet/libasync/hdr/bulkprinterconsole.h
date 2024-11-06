#pragma once

#include <ibulkprinter.h>
#include <mutex>

namespace Bulknet {

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
private:
    static std::mutex dynBlockMutex;
};

}  // namespace bulknet
