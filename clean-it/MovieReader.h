#pragma once

#include <string>

namespace ci {

	struct Movie
	{
		std::string Name;
		int Duration;
	};

	std::vector<Movie> readMovies();
}
