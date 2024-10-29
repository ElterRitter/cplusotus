#pragma once
#include "icommand.h"

#include <memory>
#include <inttypes.h>

namespace Bulkm {

/*!
 * \brief Интерфейс ICommandStorage определяет методы работы
 * с набором команд ( bulk )
 */
class ICommandStorage
{
public:
    using Ptr = std::shared_ptr<ICommandStorage>;
    ICommandStorage() = default;
    virtual ~ICommandStorage() = default;

    /*!
     * \brief Метод appendCommand определяет добавление команды в набор
     * \param cmd команда, которую нужно добавить в набор
     * \return true если добавление успешно, false если контейнер полностью заполнен
     */
    virtual bool appendCommand(const ICommand::Ptr &cmd) = 0;

    /*!
     * \brief Метод bulkSize определяет размер блока команд для хпанилища
     * \return размер хранилища
     */
    virtual std::size_t bulkSize() const noexcept = 0;

    /*!
     * \brief Метод commandsCount определяет количество команд в хранилище
     * \return количество команд
     */
    virtual std::size_t commandsCount() const noexcept = 0;

    /*!
     * \brief Метод command позволяет получить указатель на команду в хранилище
     * \param idx индекс команды
     * \return невладеющий указатель на команду
     */
    virtual ICommand::WPtr command(const std::size_t idx) noexcept = 0;

    /*!
     * \brief Метод clear очищает хранилище команд
     */
    virtual void clear() = 0;

    /*!
     * \brief Метод clone позволяет переместить внутренние данные хранилища
     * в возвращаемый объект-копию без излишних реинициализаций
     * \return указатель на хранилище с команадами исходного хранилища
     */
    virtual Ptr clone() = 0;
};

};  // namespace Bulkm
