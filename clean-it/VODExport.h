#pragma once

#include "IVODServer.h"
#include "IStreamer.h"
#include "ILogWriter.h"

import <memory>;

#define VODEXPORT __declspec(dllexport)

namespace ci {
	std::shared_ptr<IVODServer> VODEXPORT CreateVODServer(
		std::shared_ptr<IStreamer> streamer,
		std::shared_ptr<ILogWriter> logWriter);
}