import VOD;

#include "IOC.h"

using namespace Hypodermic;

std::shared_ptr<Container> IOC::operator()() {
	return _container;
}

auto IOC::Register() -> std::shared_ptr<Container> {

	// Add more registrations here on the _builder

	_builder.registerType<ConsoleWriter>().as<ci::ILogWriter>();

	_builder.registerInstanceFactory([this](ComponentContext&) {
		return CreateVODServer(_streamer, _logWriter);
	});

	return _builder.build();
}
