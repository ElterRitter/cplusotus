#pragma once

#include <ibulkprinter.h>
#include <string>

namespace Bulkm {

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
    std::string m_rootFolder;
    uint32_t m_threadId;

    std::string makeFileName(const ICommand::WPtr &cmd) const;
};

}; // namespace
