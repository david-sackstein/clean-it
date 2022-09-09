#include "MovieReader.h"

#include <gtest/gtest.h>

TEST(MovieReader, ReadSucceeds)
{
	const std::string path = ".\\movies";

	const auto movies = ci::readMovies(path);
	ASSERT_EQ(3, movies.size());
}
