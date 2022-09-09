#include "MovieReader.h"

#include <gtest/gtest.h>

TEST(MovieReader, ReadSucceeds)
{
	const std::string path = ".\\movies";

	const auto movies = readMovies(path);
	ASSERT_EQ(3, movies.size());
}
