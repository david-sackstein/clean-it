#pragma once

#include "Movie.h"

#include <stop_token>

namespace ci {
	class IStreamer  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IStreamer() = default;
		virtual void Stream(ci::Movie, std::stop_token) = 0;
	};
}
