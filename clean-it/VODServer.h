#pragma once

#include "Movie.h"

#include <format>
#include <iostream>
#include <memory>
#include <vector>
#include <cppcoro/generator.hpp>

namespace ci {
	class IMovieObserver
	{
	public:
		virtual ~IMovieObserver() = default;
		IMovieObserver() = default;

		IMovieObserver(const IMovieObserver&) = delete;
		IMovieObserver& operator=(const IMovieObserver&) = delete;
		IMovieObserver(IMovieObserver&&) = delete;
		IMovieObserver& operator=(IMovieObserver&&) = delete;

		virtual void OnPlaying(Movie) = 0;
		virtual void OnCompleted(Movie) = 0;
	};

	enum class LogLevel {
		Debug,
		Info,
		Warning,
		Error
	};

	class ConsoleLogger {
	public:
		ConsoleLogger(LogLevel level) : 
			_level(level) 
		{}

		template <typename... Args>
		void Write(LogLevel level, std::string_view format_str, Args&&... args) {
			if (level >= _level) {
				std::cout << std::vformat(
					format_str, 
					std::make_format_args(std::forward<Args>(args)...));
			}
		}

	private:

		LogLevel _level;
	};

	class VODServer : public ConsoleLogger
	{
	public:

		VODServer();
		~VODServer();

		VODServer(VODServer&& other) noexcept = default;
		VODServer(const VODServer& other) noexcept = delete;

		VODServer& operator=(VODServer&&) = default;
		VODServer& operator=(const VODServer&) = delete;

		bool Connect(std::weak_ptr<IMovieObserver>);
		void Disconnect();

		[[nodiscard]] expected<std::vector<Movie>> GetMovies() const;

		bool Play(const Movie&);
		bool Stop();

	private:

		bool _isConnected{};
		bool _isPlaying{};

		std::vector<Movie> _movies;

		std::weak_ptr<IMovieObserver> _client;

		std::jthread _playThread;
	};
}
