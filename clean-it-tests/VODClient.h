#pragma once

import <memory>;
import VOD;

#include "ManualResetEvent.h"
#include "Logger.h"

using namespace ci;
using namespace std::chrono_literals;

class VODClient :
	public IMovieObserver,
	public std::enable_shared_from_this<VODClient>
{
public:

	VODClient(
		std::shared_ptr<IVODServer>, 
		std::shared_ptr<Logger> logger);

	void TestLogin();
	void TestGetMovies();
	void TestStartStop();
	void TestCompleteDuration();

private:

	void OnPlaying(Movie) override;
	void OnCompleted(Movie)override;

	std::shared_ptr<IVODServer> _server;
	std::shared_ptr<Logger> _logger;

	ManualResetEvent _wait_for_started;
	ManualResetEvent _wait_for_stopped;
};
