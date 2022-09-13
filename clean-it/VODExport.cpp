module;

#include "VODExport.h"
#include "VODServer.h"

module VOD;

namespace ci {
	std::shared_ptr<IVODServer> CreateVODServer(
		std::shared_ptr<IStreamer> streamer,
		std::shared_ptr<ILogWriter> logWriter) {

		return std::make_shared<VODServer>(move(streamer), move(logWriter));
	}
}