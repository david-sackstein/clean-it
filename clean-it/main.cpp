#include "MovieReader.h"

#include <gtest/gtest.h>

TEST(MovieReader, ReadSucceeds)
{
	const std::string path = ".\\movies";

	const auto movies = ci::MovieReader::readMovies(path);

	ASSERT_TRUE(movies);
	ASSERT_EQ(3, movies.value().size());
}
