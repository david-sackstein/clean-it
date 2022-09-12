#include <gtest/gtest.h>

#include <VODServer.h>

TEST(TestCaseName, TestName) {

	ci::VODServer s{};
	auto a =*s.GetMovies();
	ci::expected<ci::Movie> movie = ci::Movie::create("", 1);

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
