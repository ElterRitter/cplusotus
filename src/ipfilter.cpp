#include "ipfilter.h"

#include <boost/asio.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::fstream;
using std::string;
using std::cout;
using std::endl;


IpFilter::IpFilter(std::istream &stream)
{
    string strIP;
    for( string str; std::getline(stream, str); )
    {
        std::stringstream ss(str);
        std::getline(ss, strIP, '\t');

        auto val = boost::asio::ip::address_v4::from_string(strIP).to_uint();
        m_listAddresses.push_back(val);
    }
}

IpFilter::iplist IpFilter::filter()
{
    std::sort(m_listAddresses.begin(), m_listAddresses.end(), std::greater<uint32_t>());
    return m_listAddresses;
}

IpFilter::iplist IpFilter::filterBySingleValue(const uint32_t value)
{
    iplist ret;

    std::copy_if(m_listAddresses.begin(), m_listAddresses.end(), std::back_inserter(ret),
                 [&value](const uint32_t &ipVal)
                 { return (ipVal >> 24) == value; }
                );
    return ret;
}

IpFilter::iplist IpFilter::filterByBytes(const uint16_t value)
{
    iplist ret;
    std::copy_if(m_listAddresses.begin(), m_listAddresses.end(), std::back_inserter(ret),
                 [&value](const uint32_t &ipVal)
                 {
                     bool ret = (ipVal >> 16) == value;
                     return ret;
                 });
    return ret;
}

IpFilter::iplist IpFilter::filterByAnyByte(const uint8_t value)
{
    iplist ret;
    std::copy_if(m_listAddresses.begin(), m_listAddresses.end(), std::back_inserter(ret),
                 [&value](const uint32_t &ipVal)
                 {
                    uint32_t mask = 0x000000FF;
                    uint32_t testVal = 0;
                    for(int i = 0; i < 4; i++)
                    {
                        testVal = (ipVal & mask) >> 8*i;
                        mask = mask << 8;
                        if(testVal == value)
                            return true;
                    }
                    return false;
                 });
    return ret;
}

void IpFilter::print(const iplist &&value)
{
    for(const auto &ip : value)
        cout << boost::asio::ip::address_v4(ip).to_string() << endl;
}
