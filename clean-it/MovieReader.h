#pragma once


#include "generator.h"
#include "expected.h"

#include <string>
#include <fstream>

namespace ci {
	struct Movie
	{
		std::string Name;
		int Duration;
	};
	
	class MovieReader
	{
	public:

		// read all movies from a folder named path lazily.
		[[nodiscard]] static auto readMovies(
			const std::string& path) -> generator<expected<Movie>>;

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

