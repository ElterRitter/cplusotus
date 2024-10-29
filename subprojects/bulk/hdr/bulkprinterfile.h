#pragma once

#include <ibulkprinter.h>
#include <string>

namespace Bulk {

/*!
 * \brief Класс BulkPrinterFile является реализайией интерфейса IBulkPrinter,
 * который выводит накопленные команды в файл
 */

class BulkPrinterFile : public IBulkPrinter
{
public:
    /*!
     * \brief Конструктор BulkPrinterFile
     * \param rootFolder определяет корневую папку, куда будут сохраняться файлы с командами
     */
    explicit BulkPrinterFile(const std::string &rootFolder);

    // overrided members of IBulkPrinter
    virtual void processBulk(ICommandStorage::Ptr ptrBulk) override final;

private:
    std::string m_rootFilder;

    std::string makeFileName(const ICommand::WPtr &cmd);
};

}; // namespace
