#include "VODExport.h"
#include "VODServer.h"

namespace ci {
	std::shared_ptr<IVODServer> CreateVODServer(std::shared_ptr<IStreamer> streamer) {
		return std::make_shared<VODServer>(move(streamer));
	}
}