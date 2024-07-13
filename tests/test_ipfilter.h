#pragma once
#include <ipfilter.h>
#include <gtest/gtest.h>

class Test_IpFilter : public ::testing::Test
{
protected:
    void SetUp();
    void TearDown();
};
