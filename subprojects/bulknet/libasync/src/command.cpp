#include "command.h"

using namespace Bulknet;

CommonCommand::CommonCommand(const std::string &data) : m_data{data}
{
    m_dtPoint = std::chrono::system_clock::now();
}

int64_t CommonCommand::timestamp() const noexcept
{
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(m_dtPoint);
    return now_ms.time_since_epoch().count();
}

std::ostream &operator<<(std::ostream &os, const Bulknet::ICommand::WPtr ptrCmd)
{
    auto ptr = ptrCmd.lock();
    if(!ptr)
        return os;

    auto commonCmd = std::static_pointer_cast<CommonCommand>(ptr);
    if(commonCmd)
        os << commonCmd->data();

    return os;
}

std::ostream &operator<<(std::ostream &os, const CommonCommand *cmd)
{
    os << cmd->data();
    return os;
}
