#include "MovieReader.h"

#include <filesystem>
#include <ranges>
#include <sstream>

namespace ci {

	// read all movie files from the folder named path eagerly.
	auto MovieReader::readAvailableMovies(
		const std::string& path) noexcept -> expected<std::vector<Movie>> {

		return expect([&] 
		{
			return readAvailableMovies(readMovies(path));
		});
	}

	// read one movie from a file named fileName.
	auto MovieReader::readMovie(
		const std::string& fileName) -> expected<Movie> {

		// Using the functional syntax provided by tl::expected

		return openFile(fileName)
			.and_then([&](std::ifstream file)
				{
					return readLine(file);
				})
			.and_then([&](const std::string& line)
				{
					return parseMovie(line, fileName);
				});
	}

	// read all movies from a generator eagerly.
	// Note: may throw on the first iteration of the generator.
	auto MovieReader::readAvailableMovies(
		cppcoro::generator<expected<Movie>> generator) -> std::vector<Movie> {

		using namespace std::ranges::views;

		auto movies = common(generator) |
			filter([](const expected<Movie>& e) { return e.has_value(); }) |
			transform([](const expected<Movie>& e) { return e.value<Movie>(); });

		std::vector<Movie> movieVec{};
		std::ranges::copy(movies, std::back_inserter(movieVec));

		return movieVec;
	}

	// read all movie files from the folder named path without explicitly throwing.
	// Note: the directory_iterator may throw on the first iteration of the generator.
	auto MovieReader::readMovies(
		const std::string& path) -> cppcoro::generator<expected<Movie>> {

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			co_yield readMovie(entry.path().string());
		}
	}

	// opens the file named fileName.
	auto MovieReader::openFile(
		const std::string& fileName) -> expected<std::ifstream>{

		std::ifstream file(fileName);
		if (!file.is_open()) {
			return unexpected{ "error while opening file" };
		}
		return file;
	}

	// read a line from the file.
	auto MovieReader::readLine(
		std::ifstream& file) -> expected<std::string>  {

		std::string line{};
		if (!getline(file, line)) {
			const auto* error = file.bad()
				? "error while reading file"
				: "file has the wrong format";
			return unexpected{ error };
		}
		return line;
	}

	// parse the first line in the file to determine its duration.
	auto MovieReader::parseMovie(
		const std::string& line, const std::string& fileName) -> expected<Movie> {

		std::stringstream linestream(line);
		int seconds{};
		linestream >> seconds;
		if (linestream.fail()) {
			return unexpected{ "error reading file" };
		}
		return Movie{ fileName, seconds };
	}
}
