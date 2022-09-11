#pragma once

#include "IVODServer.h"
#include "Streamer.h"
#include "Logger.h"

#include <Hypodermic/ContainerBuilder.h>

class ConsoleWriter : public ci::ILogWriter
{
public:
	void Write(std::string_view) override {}
};

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
	std::shared_ptr<ConsoleWriter> _logWriter = std::make_shared<ConsoleWriter>();
};
