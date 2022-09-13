import VOD;
import <condition_variable>;

#include "Streamer.h"

Streamer::Streamer(int speedUp) :
	_speedUp(speedUp)
{}

void Streamer::Stream(ci::Movie movie, std::stop_token token)
{
	std::mutex mutex;
	std::unique_lock lock(mutex);

	std::condition_variable_any().wait_for(
		lock,
		token,
		movie.Duration/ _speedUp,
		[&token] { return token.stop_requested(); });
}
