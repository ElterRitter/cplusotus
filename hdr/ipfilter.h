#pragma once

#include <vector>

class IpFilter
{
public:
    using iplist = std::vector<uint32_t>;
    IpFilter() = default;

private:
    iplist m_listAddresses;
};
