#include "test_ipfilter.h"

#include <fstream>
#include <boost/asio/ip/address_v4.hpp>

using std::ifstream;
using bad = boost::asio::ip::address_v4;

void Test_IpFilter::SetUp()
{
    ifstream istr("test_data.tsv");
    m_pFilter = std::make_shared<IpFilter>(istr);
}

void Test_IpFilter::TearDown()
{
    m_pFilter.reset();
}

TEST_F(Test_IpFilter, filering)
{
    auto ret = m_pFilter->filter();
    ASSERT_TRUE(ret.size() > 0);
    ASSERT_TRUE(ret.size() == 16);
    ASSERT_EQ(ret.front(), bad::from_string("219.102.120.135").to_uint());
    ASSERT_EQ(ret.back(), bad::from_string("1.29.168.152").to_uint());
}

TEST_F(Test_IpFilter, OneFirstByte)
{
    auto ret = m_pFilter->filterBySingleValue(0x01);
    ASSERT_TRUE(ret.size() == 1);
    ASSERT_TRUE(ret.front() == bad::from_string("1.29.168.152").to_uint());

    ret = m_pFilter->filterBySingleValue(0x02);
    ASSERT_TRUE(ret.empty());
}

TEST_F(Test_IpFilter, FilterTwoBytes)
{
    auto ret = m_pFilter->filterByBytes(0x442D);
    ASSERT_TRUE(ret.size() == 1);
    ASSERT_TRUE(ret.front() == bad::from_string("68.45.152.8").to_uint());

    ret = m_pFilter->filterByBytes(0x2222);
    ASSERT_TRUE(ret.empty());
}

TEST_F(Test_IpFilter, FilerAnyByte)
{
    auto ret = m_pFilter->filterByAnyByte(0x98);
    ASSERT_TRUE(ret.size() == 3);
    ASSERT_TRUE(ret.front() == bad::from_string("1.29.168.152").to_uint());
    ASSERT_TRUE(ret.back() == bad::from_string("68.45.152.8").to_uint());

    ret = m_pFilter->filterByAnyByte(0x1E);
    ASSERT_TRUE(ret.empty());
}
