#include "VODExport.h"
#include "VODClient.h"

#include <gtest/gtest.h>

using namespace ci;

TEST(TestServer, GetMovies) {
	const auto server = CreateVODServer();
	const auto client = std::make_shared<VODClient>(server);

	client->TestGetMovies();
}

TEST(TestServer, Login) {
	const auto server = CreateVODServer();
	const auto client = std::make_shared<VODClient>(server);

	client->TestLogin();
}

TEST(TestServer, StartStop) {
	const auto server = CreateVODServer();
	const auto client = std::make_shared<VODClient>(server);

	client->TestStartStop();
}

TEST(TestServer, CompleteDuration) {
	const auto server = CreateVODServer();
	const auto client = std::make_shared<VODClient>(server);

	client->TestCompleteDuration();
}
