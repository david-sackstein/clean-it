#pragma once

#include "expected.h"

#include <string>
#include <chrono>

namespace ci {
	using namespace std::chrono_literals;

	class Movie
	{
	public:
		constexpr inline static std::chrono::seconds MaxDuration = 120s;

		std::string Name;
		std::chrono::seconds Duration;

		static expected<Movie> create(
			const std::string& name, int seconds) noexcept {

			if (const auto duration = std::chrono::seconds(seconds); 
				duration > MaxDuration || duration < 1s) {
				return unexpected ("invalid duration");
			}
			return Movie(name, std::chrono::seconds(seconds));
		}

	private:

		Movie(std::string name, std::chrono::seconds seconds) :
			Name(std::move(name)),
			Duration(seconds) {
		}
	};
}