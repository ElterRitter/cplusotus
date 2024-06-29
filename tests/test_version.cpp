#include <gtest/gtest.h>

#include <versionInfo.h>

TEST(VersionTest, TestInfo)
{
    ASSERT_TRUE(versionInfo().size() > 0);
    ASSERT_FALSE(versionInfo().length() == 0);
    ASSERT_TRUE(versionInfo().find("g") != std::string_view::npos);
}

TEST(VersionTest, TestBuildNumber)
{
    ASSERT_TRUE(buildNumber() < 100) << "Build number grater than 100. May be need new tag?";
    EXPECT_TRUE(buildNumber() >= 0) << "Negative build number, need check version generation of tags";
}
