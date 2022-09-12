#pragma once

import <tl/expected.hpp>;

import <string>;
import <type_traits>;

namespace ci {
	template<typename T>
	using expected = tl::expected<T, std::string>;

	using unexpected = tl::unexpected<std::string>;

	template<typename F>
	auto expect(F&& func) noexcept -> expected<std::invoke_result_t<F>>
	{
		try
		{
			return std::invoke(std::forward<F>(func));
		}
		catch (std::exception& ex)
		{
			return unexpected(ex.what());
		}
	}
}