#include "VODServer.h"
#include "MovieReader.h"

#include <thread>
#include <condition_variable>

const std::string MoviesPath = "../Movies";

namespace ci {
	using namespace std::chrono_literals;

	VODServer::VODServer(
		std::shared_ptr<IStreamer> streamer, 
		std::shared_ptr<ILogWriter> logWriter)
	:
		_logger(move(logWriter), LogLevel::Debug),
		_streamer(move(streamer))
	{}

	VODServer::~VODServer() {
		VODServer::Stop();
	}

	bool VODServer::Connect(std::weak_ptr<IMovieObserver> client)
	{
		if (_isConnected) {
			_logger.Write(LogLevel::Warning, "Already connected");
			return false;
		}

		_client = std::move(client);
		_isConnected = true;

		_logger.Write(LogLevel::Info, "Connected");

		return true;
	}

	void VODServer::Disconnect()
	{
		Stop();
		_isConnected = false;
	}

	expected<std::vector<Movie>> VODServer::GetMovies() const {
		if (!_isConnected) {
			return {};
		}

		return MovieReader::readAvailableMovies(MoviesPath);
	}

	bool VODServer::Play(const Movie& movie)
	{
		if (_isPlaying) {
			return false;
		}

		_playThread = std::jthread([this, movie](const std::stop_token& token)
			{
				doPlay(movie, token);
			});

		_isPlaying = true;
		return true;
	}

	bool VODServer::Stop()
	{
		if (!_isPlaying) {
			return false;
		}

		_playThread.request_stop();
		_playThread.join();

		_isPlaying = false;
		return true;
	}

	void VODServer::doPlay(const Movie& movie, const std::stop_token& token) const {

		if (const auto c = _client.lock())
		{
			c->OnPlaying(movie);
		}

		_streamer->Stream(movie, token);

		if (const auto c = _client.lock())
		{
			c->OnCompleted(movie);
		}
	}
}