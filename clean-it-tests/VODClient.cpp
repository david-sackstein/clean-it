#include <gtest/gtest.h>

#include "VODClient.h"

using namespace std::chrono_literals;
using namespace ci;

VODClient::VODClient(std::shared_ptr<VODServer> server) :
	_server(std::move(server))
{
}

void VODClient::OnPlaying(Movie)
{
	_wait_for_started.signal();
}

void VODClient::OnCompleted(Movie)
{
	_wait_for_stopped.signal();
}

void VODClient::TestLogin()
{
	bool connected = _server->Connect(weak_from_this());
	ASSERT_TRUE(connected);

	connected = _server->Connect(weak_from_this());
	ASSERT_FALSE(connected);

	_server->Disconnect();

	connected = _server->Connect(weak_from_this());
	ASSERT_TRUE(connected);
}

void VODClient::TestGetMovies() {
	auto movies = _server->GetMovies();
	ASSERT_TRUE(movies && movies->empty());

	const bool loggedIn = _server->Connect(weak_from_this());
	ASSERT_TRUE(loggedIn);

	movies = _server->GetMovies();
	ASSERT_FALSE(movies && movies->empty());
}

void VODClient::TestStartStop()
{
	const bool loggedIn = _server->Connect(weak_from_this());
	ASSERT_TRUE(loggedIn);

	const auto movies = _server->GetMovies();
	ASSERT_TRUE(movies && !movies->empty());

	const auto first = *movies->begin();

	const bool isPlaying = _server->Play(first);
	ASSERT_TRUE(isPlaying);

	const auto receivedPlaying = _wait_for_started.wait_for(1s);
	ASSERT_TRUE(receivedPlaying);

	const auto isStopped = _server->Stop();
	ASSERT_TRUE(isStopped);

	const auto receivedStopped = _wait_for_stopped.wait_for(1s);
	ASSERT_TRUE(receivedStopped);
}

void VODClient::TestCompleteDuration() {
	const bool loggedIn = _server->Connect(weak_from_this());
	ASSERT_TRUE(loggedIn);

	const auto movies = _server->GetMovies();
	ASSERT_TRUE(movies && !movies->empty());

	const auto first = *movies->begin();

	bool isPlaying = _server->Play(first);
	ASSERT_TRUE(isPlaying);

	isPlaying = _server->Play(first);
	ASSERT_FALSE(isPlaying);

	const auto receivedPlaying = _wait_for_started.wait_for(1s);
	ASSERT_TRUE(receivedPlaying);

	const auto receivedStopped = _wait_for_stopped.wait_for(20s);
	ASSERT_TRUE(receivedStopped);
}
