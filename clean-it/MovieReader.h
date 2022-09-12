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

		// read all available movies from a folder named path eagerly.
		[[nodiscard]] static auto readAvailableMovies(
			const std::string& path) noexcept -> expected<std::vector<Movie>>;

		// read one movie from a file named fileName.
		[[nodiscard]] static auto readMovie(
			const std::string& fileName) -> expected<Movie>;

	private:

		// read all movies from a generator eagerly.
		// Note: may throw on the first iteration of the generator.
		[[nodiscard]] static auto readAvailableMovies(
			generator<expected<Movie>> generator) -> std::vector<Movie>;

		// read all movie files from the folder named path without explicitly throwing.
		// Note: the directory_iterator may throw on the first iteration of the generator.
		[[nodiscard]] static auto readMovies(
			const std::string& path)->generator<expected<Movie>>;

		// opens the file named fileName.
		[[nodiscard]] static auto openFile(
			const std::string& fileName) -> expected<std::ifstream>;

		// read a line from the file.
		[[nodiscard]] static auto readLine(
			std::ifstream& file) -> expected<std::string>;

		// parse the first line in the file to determine its duration.
		[[nodiscard]] static auto parseMovie(
			const std::string& fileLine, const std::string& fileName) -> expected<Movie>;
	};
}

