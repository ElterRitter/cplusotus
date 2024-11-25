#pragma once
#include <memory>

namespace Bulknet {

/*!
 * \brief Интерфейс ICommand определяет методы для команд и типы команд
 */
class ICommand
{
public:
    using Ptr = std::shared_ptr<ICommand>;
    using WPtr = std::weak_ptr<ICommand>;

    ICommand() = default;
    virtual ~ICommand() = default;

    /*!
     * \brief Перечисление Type определяет возможные типы команд
     */
    enum class Type
    {
        common,         ///< команда общего вида
        dynBlockOpen,   ///< команда открывающая динамический блок
        dynBlockClose   ///< команда закрывающая динамический блок
    };

    /*!
     * \brief Метод type позволяет получить тип команды
     * \return тип команды
     */
    virtual Type type() const noexcept = 0;
};

};  // namespace bulknet
