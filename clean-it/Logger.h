#pragma once

#include <format>
#include <iostream>

namespace ci {

	enum class LogLevel {
		Debug,
		Info,
		Warning,
		Error
	};

	class ConsoleLogger {
	public:
		ConsoleLogger(LogLevel level) : 
			_level(level) 
		{}

		template <typename... Args>
		void Write(LogLevel level, std::string_view format_str, Args&&... args) {
			if (level >= _level) {
				std::cout << std::vformat(
					format_str, 
					std::make_format_args(std::forward<Args>(args)...));
			}
		}

	private:

		LogLevel _level;
	};
}
