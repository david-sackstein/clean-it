#pragma once

#include <tl/expected.hpp>

#include <string>
#include <vector>
#include <fstream>

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

	class MovieReader
	{
	public:

		// read all movies from a folder named path without explicit throw.
		[[nodiscard]] static auto readMovies(
			const std::string& path) -> expected<std::vector<expected<Movie>>>;

		// read one movie from a file named fileName without explicit throw.
		[[nodiscard]] static auto readMovie(
			const std::string& fileName) -> expected<Movie>;

	private:

		// opens the file without explicit throw
		[[nodiscard]] static auto openFile(
			const std::string& fileName) -> expected<std::ifstream>;

		// read the first line in the file without explicit throw
		[[nodiscard]] static auto readLine(
			std::ifstream& file) -> expected<std::string>;

		// read the movie file and determine its duration without explicit throw
		[[nodiscard]] static auto parseMovie(
			const std::string& fileLine, const std::string& fileName) -> expected<Movie>;
	};
}