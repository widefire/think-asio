#pragma once

#include <iostream>
#include "asio.hpp"

namespace gra
{
	typedef std::function<void()> FuncHeartTimeout;
	class HeartTimer
	{
	public:
		static std::shared_ptr<HeartTimer> NewTimer(size_t second, FuncHeartTimeout func);
		HeartTimer();
		~HeartTimer();
		void StopTimer();
	private:
		void StartTimer();
		void TimerHandler(const asio::error_code &ec);
	private:
		FuncHeartTimeout _timeoutFunc;
		std::chrono::nanoseconds _timeoutValue;
		asio::steady_timer _timer;
		asio::error_code _errCode;
		volatile bool _stoped = false;
		std::mutex _mux;
		std::condition_variable _con;
		int _callbackCount = 0;
	};
}


