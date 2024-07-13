#include "ipfilter.h"

#include <boost/asio.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;


IpFilter::iplist IpFilter::filter()
{
    string strIP;
    for( string str; std::getline(std::cin, str); )
    {
        std::stringstream ss(str);
        std::getline(ss, strIP, '\t');

        auto val = boost::asio::ip::address_v4::from_string(strIP).to_uint();
        m_listAddresses.push_back(val);
    }

    std::sort(m_listAddresses.begin(), m_listAddresses.end(), std::greater<uint32_t>());

    return m_listAddresses;
}

void IpFilter::print(const iplist &&value)
{
    for(const auto &ip : value)
        cout << boost::asio::ip::address_v4(ip).to_string() << endl;
}
