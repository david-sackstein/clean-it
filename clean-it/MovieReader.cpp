#include "MovieReader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace ci {

	expected<Movie> readMovie(const std::string& fileName);

	// read all movie files from the folder named path without explicitly throwing.
	expected<std::vector<expected<Movie>>> readMovies(const std::string& path)
	{
		std::vector<expected<Movie>> movies;

		// use the overload that excepts an error_code. Note: may still throw std::bad_alloc. 
		std::error_code ec;

		for (const auto& entry : std::filesystem::directory_iterator(path, ec)) {
			movies.emplace_back(readMovie(entry.path().string()));
		}

		// if an error occurred return unexpected
		if (ec){
			return unexpected{ ec.message() };
		}
		return movies;
	}

	auto openFile(const std::string& fileName) -> expected<std::ifstream>;
	auto readLine(std::ifstream& file) -> expected<std::string>;
	auto parseMovie(const std::string& line, const std::string& fileName) -> expected<Movie>;

	// read a movie file and determine its duration without explicitly throwing
	expected<Movie> readMovie(const std::string& fileName) {

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
	auto openFile(const std::string& fileName) -> expected<std::ifstream>
	{
		std::ifstream file(fileName);
		if (!file.is_open()) {
			return unexpected{ "error while opening file" };
		}
		return file;
	}

	// read the first line in the file without explicit throw
	auto readLine(std::ifstream& file) -> expected<std::string>
	{
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
	auto parseMovie(const std::string& line, const std::string& fileName) -> expected<Movie> {
		std::stringstream linestream(line);
		int seconds{};
		linestream >> seconds;
		if (linestream.fail()) {
			return unexpected{ "error reading file" };
		}
		return Movie{ fileName, seconds };
	}
}
