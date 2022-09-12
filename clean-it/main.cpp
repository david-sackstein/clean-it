#include "MovieReader.h"

#include <gtest/gtest.h>

#include <ranges>

using namespace std::ranges::views;
using namespace ci;

TEST(MovieReader, ReadMovieSucceeds) {
	const std::string path = "./Movies";

	auto allMovies = MovieReader::readAvailableMovies(path);

	ASSERT_TRUE(allMovies && allMovies->size() == 3);
}