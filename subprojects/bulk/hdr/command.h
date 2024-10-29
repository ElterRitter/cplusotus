#pragma once

#include <icommand.h>

#include <string>
#include <iostream>
#include <chrono>

namespace Bulk {

/*!
 * \brief Класс DynBlockOpenCommand является реализацией интерфейса ICommand,
 * которая отмечает начало динамического блока команд
 */
class DynBlockOpenCommand : public ICommand
{
public:
    DynBlockOpenCommand() = default;

    // overrided ICommand methods
    virtual ICommand::Type type() const noexcept override final { return ICommand::Type::dynBlockOpen; };
};

/*!
 * \brief Класс DynBlockCloseCommand является реализацией интерфейса ICommand,
 * которая отмечает завершение динамического блока команд
 */
class DynBlockCloseCommand : public ICommand
{
public:
    DynBlockCloseCommand() = default;

    // override ICommand methods
    virtual ICommand::Type type() const noexcept override final { return ICommand::Type::dynBlockClose; }
};

/*!
 * \brief Класс CommonCommand является реализацией интерфейса ICommand,
 * которая представляет собой команду общего вида, содержащую
 * строку данных
 */
class CommonCommand : public ICommand
{
public:
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    explicit CommonCommand(const std::string &data);
//    virtual ~CommonCommand() { std::cout << "destructor for command: " << m_data << " !" << std::endl; }

    // override ICommand methods
    virtual ICommand::Type type() const noexcept override final { return ICommand::Type::common; }

    const std::string& data() const noexcept { return m_data; }
    int64_t timestamp() const noexcept;
private:
    std::string m_data;
    TimePoint m_dtPoint;
};

};  // namespace Bulk

/*!
 * \brief operator << перегруженный оператор для вывода команды в выводной поток
 * \param os поток вывода ( файл, консоль и т.п. )
 * \param ptrCmd команда, которую нужно вывести в консоль
 * \return поток вывода
 */
std::ostream& operator<< (std::ostream& os, const Bulk::ICommand::WPtr ptrCmd);
