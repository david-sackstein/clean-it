#pragma once

#include "Streamer.h"
#include "IVODServer.h"

#include <Hypodermic/ContainerBuilder.h>

class IOC
{
	using Container = Hypodermic::Container;
	using Builder = Hypodermic::ContainerBuilder;

public:

	std::shared_ptr<Container> operator()();

private:

	std::shared_ptr<Container> Register();

	Builder _builder;

	std::shared_ptr<Container> _container = Register();
	std::shared_ptr<Streamer> _streamer = std::make_shared<Streamer>(10);
};
