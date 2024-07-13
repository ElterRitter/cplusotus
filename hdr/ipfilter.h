#pragma once

#include <vector>
#include <cstdint>

class IpFilter
{
public:
    using iplist = std::vector<uint32_t>;
    IpFilter() = default;

    iplist filter();
    iplist filterBySingleValue(const uint32_t value);
    iplist filterByBytes(const uint16_t value);

    void print(const iplist&& value);

private:
    iplist m_listAddresses;
};
