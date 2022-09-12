#include "MovieReader.h"

#include <gtest/gtest.h>

TEST(MovieReader, ReadMovieSucceeds) {
	const std::string path = "../Movies";

	auto allMovies = ci::MovieReader::readAvailableMovies(path);

	ASSERT_TRUE(allMovies && allMovies->size() == 3);
}