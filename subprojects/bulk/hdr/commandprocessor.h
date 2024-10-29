#pragma once
#include "icommandstorage.h"
#include "ibulkpublisher.h"

#include <string>
#include <vector>
#include <stack>

namespace Bulk {

/*!
 * \brief Класс CommandProcessor является процессором считанных данных.
 * Из считанных данных формируется команда и исполняется в соответствии
 * со своим типом.
 */
class CommandProcessor : IBulkPublisher
{
public:
    /*!
     * \brief CommandProcessor конструктор
     * \param bulkSize рамер пачки команды
     */
    explicit CommandProcessor(uint32_t bulkSize);
    virtual ~CommandProcessor();    ///< деструктор

    // override members of IBulkPublisher
    void subscribePrinter(const IBulkPrinter::Ptr ptrPrinter) override final;
    void unsubscribePrinter(const IBulkPrinter::Ptr ptrPrinter) override final;

    /*!
     * \brief Метод processingCommand формирует команду из входящей строки
     * и обрабатывает её в соответствии с типом сформированной команды
     * \param cmd строка считанных данных
     */
    void processingCommand(const std::string &cmd);

    /*!
     * \brief Метод finalize выводит текущий блок команд, если этот
     * блок является "базовым", не динамическим.
     */
    void finalize();

private:
    std::stack<ICommandStorage::Ptr> m_storages;
    std::vector<IBulkPrinter::Ptr> m_printers;

    void publishBulk();
};

}; // namespace Bulk
