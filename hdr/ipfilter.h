#pragma once

#include <vector>
#include <cstdint>
#include <istream>

class IpFilter
{
public:
    using iplist = std::vector<uint32_t>;
    explicit IpFilter(std::istream &stream);

    iplist filter();
    iplist filterBySingleValue(const uint32_t value);
    iplist filterByBytes(const uint16_t value);
    iplist filterByAnyByte(const uint8_t value);

    void print(const iplist&& value);

private:
    iplist m_listAddresses;
};
