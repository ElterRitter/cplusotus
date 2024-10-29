#pragma once

#include "icommand.h"

#include <string>

namespace Bulkm {

/*!
 * \brief Класс-синглтон CommandFabric реализует создание команд из текстовых данных
 */

class CommandFabric
{
public:
    static CommandFabric* instance();   //< получение экземпляра синглтона

    /*!
     * \brief Метод makeCommand формирует команду из строки
     * \param data строка данных для формирования команды
     * \return команда в виде абстрактного интерфейса
     */
    ICommand::Ptr makeCommand(const std::string &data) const;

private:
    CommandFabric() = default;
};

}; // namespace bulk
