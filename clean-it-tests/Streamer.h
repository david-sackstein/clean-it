#pragma once

#include "IStreamer.h"

class Streamer : public ci::IStreamer
{
public:
	explicit Streamer(int speedUp);

	void Stream(ci::Movie, std::stop_token) override;

private:
	int _speedUp;
};
