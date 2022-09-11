#include "VODExport.h"
#include "VODClient.h"
#include "IOC.h"

#include <gtest/gtest.h>

using namespace ci;

IOC ioc;

TEST(TestServer, GetMovies) {
	const auto client = ioc()->resolve<VODClient>();

	client->TestGetMovies();
}

TEST(TestServer, Login) {
	const auto client = ioc()->resolve<VODClient>();

	client->TestLogin();
}

TEST(TestServer, StartStop) {
	const auto client = ioc()->resolve<VODClient>();

	client->TestStartStop();
}

TEST(TestServer, CompleteDuration) {
	const auto client = ioc()->resolve<VODClient>();

	client->TestCompleteDuration();
}
