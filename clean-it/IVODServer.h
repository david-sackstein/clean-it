#pragma once

#include "IMovieObserver.h"

#include <memory>
#include <vector>

namespace ci {
	class IVODServer																	 // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IVODServer() = default;

		virtual bool Connect(std::weak_ptr<IMovieObserver>) = 0;
		virtual void Disconnect() = 0;

		[[nodiscard]] virtual expected<std::vector<Movie>> GetMovies() const = 0;

		virtual bool Play(const Movie&) = 0;
		virtual bool Stop() = 0;
	};
}
