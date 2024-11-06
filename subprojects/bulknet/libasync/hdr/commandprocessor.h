#pragma once
#include "icommandstorage.h"
#include "ibulkpublisher.h"

#include <boost/signals2.hpp>

#include <string>
#include <stack>

namespace Bulknet {

/*!
 * \brief Класс CommandProcessor является процессором считанных данных.
 * Из считанных данных формируется команда и исполняется в соответствии
 * со своим типом.
 */
class CommandProcessor : public IBulkPublisher
{
public:
    using Ptr = std::unique_ptr<CommandProcessor>;
    using SPtr = std::shared_ptr<CommandProcessor>;
    /*!
     * \brief CommandProcessor конструктор
     * \param bulkSize рамер пачки команды
     */
    explicit CommandProcessor(uint32_t bulkSize);
    virtual ~CommandProcessor();    ///< деструктор

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
};

}; // namespace Bulknet
