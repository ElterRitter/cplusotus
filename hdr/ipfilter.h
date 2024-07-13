#pragma once

#include <vector>
#include <cstdint>

class IpFilter
{
public:
    using iplist = std::vector<uint32_t>;
    IpFilter() = default;

private:
    iplist m_listAddresses;
};
