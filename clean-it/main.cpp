#include <gtest/gtest.h>

#include <vector>

#include "MovieReader.h"

TEST(MovieReader, ReadSucceeds)
{
	const auto movies = ci::readMovies();
	ASSERT_EQ(3, movies.size());
}
