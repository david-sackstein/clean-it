#pragma once

#include "VODExport.h"
#include "ManualResetEvent.h"

using namespace ci;

#include <memory>

class VODClient :
	public IMovieObserver,
	public std::enable_shared_from_this<VODClient>
{
public:

	VODClient(std::shared_ptr<IVODServer>);

	void TestLogin();
	void TestGetMovies();
	void TestStartStop();
	void TestCompleteDuration();

private:

	void OnPlaying(Movie) override;
	void OnCompleted(Movie)override;

	std::shared_ptr<IVODServer> _server;

	ManualResetEvent _wait_for_started;
	ManualResetEvent _wait_for_stopped;
};
