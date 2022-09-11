#pragma once

#include <string_view>

namespace ci {

	class ILogWriter  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~ILogWriter() = default;
		virtual void Write(std::string_view) = 0;
	};
}
