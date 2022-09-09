#include "MovieReader.h"

#include <filesystem>
#include <sstream>

namespace ci {

	// read all movie files from the folder named path without explicitly throwing.
	// Note: the directory_iterator may throw on the first iteration of the generator.
	auto MovieReader::readMovies(
		const std::string& path) -> generator<expected<Movie>> {

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			co_yield readMovie(entry.path().string());
		}
	}

	// read a movie file and determine its duration without explicitly throwing
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

	// opens the file without explicit throw
	auto MovieReader::openFile(
		const std::string& fileName) -> expected<std::ifstream> {

		std::ifstream file(fileName);
		if (!file.is_open()) {
			return unexpected{ "error while opening file" };
		}
		return file;
	}

	// read the first line in the file without explicit throw
	auto MovieReader::readLine(
		std::ifstream& file) -> expected<std::string> {

		std::string line{};
		if (!getline(file, line)) {
			const auto* error = file.bad()
				? "error while reading file"
				: "file has the wrong format";
			return unexpected{ error };
		}
		return line;
	}

	// read the movie file and determine its duration without explicit throw
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
