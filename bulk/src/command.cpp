#include "command.h"


CommonCommand::CommonCommand(const std::string &data) : m_data{data}
{
    m_dtPoint = std::chrono::system_clock::now();
}

int64_t CommonCommand::timestamp() const noexcept
{
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(m_dtPoint);
    return now_ms.time_since_epoch().count();
}

std::ostream &operator<<(std::ostream &os, const ICommand::Ptr ptrCmd)
{
    auto commonCmd = std::static_pointer_cast<CommonCommand>(ptrCmd);
    if(commonCmd)
        os << commonCmd->data();

    return os;
}

std::ostream &operator<<(std::ostream &os, const CommonCommand *cmd)
{
    os << cmd->data();
    return os;
}
