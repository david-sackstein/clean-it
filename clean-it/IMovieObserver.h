#pragma once

#include "Movie.h"

namespace ci {
	class IMovieObserver                              // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IMovieObserver() = default;

		virtual void OnPlaying(Movie) = 0;
		virtual void OnCompleted(Movie) = 0;
	};
}
