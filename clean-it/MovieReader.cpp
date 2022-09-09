#include "MovieReader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace ci {
	Movie readMovieFile(const std::string& fileName);

	// read all movies from the folder at path
	std::vector<Movie> readMovies(const std::string& path)
	{
		std::vector<Movie> movies;

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			movies.emplace_back(readMovieFile(entry.path().string()));
		}

		return movies;
	}

	// read a movie file and determine its duration.
	Movie readMovieFile(const std::string& fileName)
	{
		// open the file
		std::ifstream file(fileName);
		if (!file.is_open())
			throw std::runtime_error("error while opening file");

		// read a line
		std::string line;
		if (getline(file, line)) {

			// parse the line and read the duration
			std::stringstream linestream(line);
			int seconds{};
			linestream >> seconds;
			if (linestream.fail()) {
				throw std::runtime_error("error reading file");
			}
			// if successful, store the Movie in the vector
			return { fileName, seconds };
		}
		// if reading the file failed, throw
		if (file.bad()) {
			throw std::runtime_error("error while reading file");
		}
		// if reading the line failed, throw
		throw std::runtime_error("file has the wrong format");
	}
}
