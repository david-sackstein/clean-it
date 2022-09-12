#pragma once

import <mutex>;
import <condition_variable>;

class ManualResetEvent
{
public:
	void wait()
	{
		std::unique_lock lock(_mu);
		_cond.wait(lock, [this] { return _isSet; });
	}

	bool wait_for(const std::chrono::milliseconds ms)
	{
		std::unique_lock lock(_mu);
		return _cond.wait_for(lock, ms, [this] { return _isSet; });
	}

	void signal()
	{
		std::lock_guard lock(_mu);
		_isSet = true;
		_cond.notify_one();
	}

	void reset()
	{
		std::lock_guard lock(_mu);
		_isSet = false;
	}

private:

	bool _isSet{ false };
	std::mutex _mu{};
	std::condition_variable _cond;
};