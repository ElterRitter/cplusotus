#pragma once
#include <ipfilter.h>
#include <gtest/gtest.h>

#include <memory>

class Test_IpFilter : public ::testing::Test
{
protected:
    void SetUp();
    void TearDown();

    std::shared_ptr<IpFilter> m_pFilter;
};
