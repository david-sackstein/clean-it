#pragma once

#include "ILogWriter.h"

import <format>;

namespace ci {

	enum class LogLevel {
		Debug,
		Info,
		Warning,
		Error
	};

	class Logger {
	public:
		Logger(std::shared_ptr<ILogWriter> writer, LogLevel level = LogLevel::Error) :
			_writer(move(writer)),
			_level(level) 
		{}

		template <typename... Args>
		void Write(LogLevel level, std::string_view format_str, Args&&... args) {
			if (level >= _level) {
				_writer->Write(std::vformat(
					format_str, 
					std::make_format_args(std::forward<Args>(args)...)));
			}
		}

	private:

		std::shared_ptr<ILogWriter> _writer;
		LogLevel _level;
	};
}
