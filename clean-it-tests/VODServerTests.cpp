#include "VODExport.h"
#include "VODClient.h"
#include "Streamer.h"

#include <gtest/gtest.h>

using namespace ci;

TEST(TestServer, GetMovies) {
	const auto streamer = std::make_shared<Streamer>(10);
	const auto server = CreateVODServer(streamer);
	const auto client = std::make_shared<VODClient>(server);

	client->TestGetMovies();
}

TEST(TestServer, Login) {
	const auto streamer = std::make_shared<Streamer>(10);
	const auto server = CreateVODServer(streamer);
	const auto client = std::make_shared<VODClient>(server);

	client->TestLogin();
}

TEST(TestServer, StartStop) {
	const auto streamer = std::make_shared<Streamer>(10);
	const auto server = CreateVODServer(streamer);
	const auto client = std::make_shared<VODClient>(server);

	client->TestStartStop();
}

TEST(TestServer, CompleteDuration) {
	const auto streamer = std::make_shared<Streamer>(10);
	const auto server = CreateVODServer(streamer);
	const auto client = std::make_shared<VODClient>(server);

	client->TestCompleteDuration();
}
