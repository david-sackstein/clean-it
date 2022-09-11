#include "VODExport.h"
#include "VODServer.h"

namespace ci {
	std::shared_ptr<IVODServer> CreateVODServer() {
		return std::make_shared<VODServer>();
	}
}