#include "MovieReader.h"

#include <gtest/gtest.h>

#include <ranges>

using namespace std::ranges::views;
using namespace ci;

TEST(MovieReader, ReadMovieSucceeds) {
	const std::string path = ".\\Movies";

	auto allMovies = expect([&path] {
		return std::ranges::all_of(
			MovieReader::readMovies(path),
			[](const auto& m)
			{
				return m.has_value();
			}
		);
		});

	ASSERT_TRUE(allMovies && allMovies.value());
}