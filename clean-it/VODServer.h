#pragma once

#include "Movie.h"

#include <format>
#include <iostream>
#include <memory>
#include <vector>
#include <cppcoro/generator.hpp>

#include "VODExport.h"

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

		VODEXPORT VODServer();
		VODEXPORT ~VODServer();

		VODServer(VODServer&& other) noexcept = default;
		VODServer(const VODServer& other) noexcept = delete;

		VODServer& operator=(VODServer&&) = default;
		VODServer& operator=(const VODServer&) = delete;

		bool VODEXPORT Connect(std::weak_ptr<IMovieObserver>);
		void VODEXPORT Disconnect();

		[[nodiscard]] expected<std::vector<Movie>> VODEXPORT GetMovies() const;

		bool VODEXPORT Play(const Movie&);
		bool VODEXPORT Stop();

	private:

		bool _isConnected{};
		bool _isPlaying{};

		void doPlay(const Movie&, const std::stop_token& token) const;

		std::vector<Movie> _movies;
		std::weak_ptr<IMovieObserver> _client;
		std::jthread _playThread;
	};
}
