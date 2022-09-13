module;

#include "VODExport.h"
#include "VODServer.h"

export module VOD;

namespace ci {
	export std::shared_ptr<IVODServer> VODEXPORT CreateVODServer(
		std::shared_ptr<IStreamer> streamer,
		std::shared_ptr<ILogWriter> logWriter);

	export class Movie;
	export class IVODServer;
	export class ILogWriter;
	export class IMovieObserver;
	export class IStreamer;
}
