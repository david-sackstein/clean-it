#include <gtest/gtest.h>

#include <vector>

#include "MovieReader.h"

TEST(MovieReader, ReadSucceeds)
{
	const std::string path = ".\\movies";

	const auto movies = ci::readMovies(path);
	ASSERT_EQ(3, movies.size());
}
