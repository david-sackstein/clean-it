#include "MovieReader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace ci {

    expected<Movie> readMovie(const std::string& fileName);

    // read all movie files from the folder named path without explicitly throwing.
    expected <std::vector<expected<Movie>>> readMovies(const std::string& path)
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

    // read a movie file and determine its duration without explicitly throwing
    expected<Movie> readMovie(const std::string& fileName) {
        // open the file
        std::ifstream file(fileName);
        if (!file.is_open())
            return unexpected{ "error while opening file" };

        // read a line
        std::string line;
        if (getline(file, line)) {

        	// parse the line and read the duration
            std::stringstream linestream(line);
            int seconds{};
            linestream >> seconds;
            if (linestream.fail()) {
                return unexpected{ "error reading file" };
            }
            // if successful, store the Movie in the vector
            return Movie{ fileName, seconds };
        }
        // if reading the file failed, return unexpected
        if (file.bad()) {
            return unexpected{ "error while reading file" };
        }
        // if reading the line failed, return unexpected
        return unexpected{ "file has the wrong format" };
    }
}

