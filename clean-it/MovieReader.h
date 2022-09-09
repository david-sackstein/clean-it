#pragma once

#include <tl/expected.hpp>

#include <string>
#include <vector>

namespace ci {
	struct Movie
	{
		std::string Name;
		int Duration;
	};

	// customizations of tl::expected

	template<typename T>
	using expected = tl::expected<T, std::string>;

	using unexpected = tl::unexpected<std::string>;

	expected<std::vector<expected<Movie>>> readMovies(const std::string& path);
}