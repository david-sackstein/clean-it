#pragma once

#include "IVODServer.h"

#include <memory>

#define VODEXPORT __declspec(dllexport)

namespace ci {
	std::shared_ptr<IVODServer> VODEXPORT CreateVODServer();
}


