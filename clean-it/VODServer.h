#pragma once

#include "IStreamer.h"
#include "IVODServer.h"
#include "Logger.h"

#include <memory>
#include <vector>


namespace ci {
	class VODServer : public IVODServer, public ConsoleLogger
	{
	public:

		VODServer(std::shared_ptr<IStreamer> streamer);
		~VODServer() override;

		VODServer(VODServer&& other) noexcept = default;
		VODServer(const VODServer& other) noexcept = delete;

		VODServer& operator=(VODServer&&) = default;
		VODServer& operator=(const VODServer&) = delete;

		bool Connect(std::weak_ptr<IMovieObserver>) override;
		void Disconnect() override;

		[[nodiscard]] expected<std::vector<Movie>> GetMovies() const override;

		bool Play(const Movie&) override;
		bool Stop() override;

	private:

		bool _isConnected{};
		bool _isPlaying{};

		void doPlay(const Movie&, const std::stop_token& token) const;

		std::shared_ptr<IStreamer> _streamer;
		std::vector<Movie> _movies;
		std::weak_ptr<IMovieObserver> _client;
		std::jthread _playThread;
	};
}
