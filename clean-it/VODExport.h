#pragma once

#include "IVODServer.h"
#include "IStreamer.h"

#include <memory>

#define VODEXPORT __declspec(dllexport)

namespace ci {
	std::shared_ptr<IVODServer> VODEXPORT CreateVODServer(
		std::shared_ptr<IStreamer> streamer);
}


