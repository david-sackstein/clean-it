#pragma once

#include "expected.h"

#include <string>
#include <chrono>

namespace ci {
	using namespace std::chrono_literals;

	class Movie
	{
	public:
		const std::chrono::seconds MaxDuration = 120s;

		std::string Name;
		std::chrono::seconds Duration;

		static expected<Movie> create(
			const std::string& name, int seconds) noexcept {
			return expect([&] {
				return Movie(name, std::chrono::seconds(seconds));
			});
		}

	private:

		Movie(std::string name, std::chrono::seconds seconds) :
			Name(std::move(name)),
			Duration(seconds) {

			if (Duration > MaxDuration || Duration < 1s) {
				throw std::runtime_error("invalid duration");
			}
		}
	};
}