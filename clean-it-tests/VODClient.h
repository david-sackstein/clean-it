#pragma once

#include "VODServer.h"
#include "ManualResetEvent.h"

#include <memory>

using namespace ci;

class VODClient :
	public IMovieObserver,
	public std::enable_shared_from_this<VODClient>
{
public:

	VODClient(std::shared_ptr<VODServer>);

	void TestLogin();
	void TestGetMovies();
	void TestStartStop();
	void TestCompleteDuration();

private:

	void OnPlaying(Movie) override;
	void OnCompleted(Movie)override;

	std::shared_ptr<VODServer> _server;

	ManualResetEvent _wait_for_started;
	ManualResetEvent _wait_for_stopped;
};
