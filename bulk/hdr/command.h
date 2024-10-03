#pragma once

#include <icommand.h>

#include <string>
#include <iostream>

class DynBlockOpenCommand : public ICommand
{
public:
    DynBlockOpenCommand() = default;

    // overrided ICommand methods
    virtual ICommand::Type type() const noexcept override final { return ICommand::Type::dynBlockOpen; };
};

class DynBlockCloseCommand : public ICommand
{
public:
    DynBlockCloseCommand() = default;

    // override ICommand methods
    virtual ICommand::Type type() const noexcept override final { return ICommand::Type::dynBlockClose; }
};

class CommonCommand : public ICommand
{
public:
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

std::ostream& operator<< (std::ostream& os, const ICommand::WPtr ptrCmd);
