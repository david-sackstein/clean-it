#include <filesystem>
#include <fstream>
#include <sstream>

#include "MovieReader.h"

namespace ci {

    std::vector<Movie> readMovies()
    {
        std::vector<Movie> movies;
        std::string path = ".\\movies";

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            // read the movie file and determine its duration.
            std::ifstream file(entry.path());

            // open the file
            std::string name = entry.path().string();
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
                movies.emplace_back(entry.path().string(), seconds);
            }
            else {
                // if reading the file failed, throw
                if (file.bad()) {
                    throw std::runtime_error("error while reading file");
                }
                // if reading the line failed, throw
                throw std::runtime_error("file has the wrong format");
            }
        }

        return movies;
    }
}
