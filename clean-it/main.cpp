#include "MovieReader.h"

#include <gtest/gtest.h>

TEST(MovieReader, ReadSucceeds)
{
	const std::string path = ".\\movies";

	ASSERT_TRUE(std::ranges::all_of(
		ci::MovieReader::readMovies(path),
		[](const auto& m)
		{
			return m.has_value();
		}
	));
}
