#include "HeartTimer.h"
#include "ForeverIOService.h"

namespace gra
{
	std::shared_ptr<HeartTimer> HeartTimer::NewTimer(size_t second, FuncHeartTimeout func)
	{
		if (second<=0||func==nullptr)
		{
			return nullptr;
		}
		auto ht = std::make_shared<HeartTimer>();
		ht->_timeoutFunc = func;
		ht->_timeoutValue = std::chrono::seconds(second);
		ht->StartTimer();
		return ht;
	}
	HeartTimer::HeartTimer()
		:_timer(ForeverIOService::Get())
	{

	}


	HeartTimer::~HeartTimer()
	{
	}

	void HeartTimer::StopTimer()
	{
		if (_stoped)
		{
			return;
		}
		_stoped = true;
		_timer.cancel();
	}

	void HeartTimer::StartTimer()
	{
		_stoped = false;
		_timer.expires_after(_timeoutValue);
		_timer.async_wait(std::bind(&HeartTimer::TimerHandler, this, _errCode));
	}

	void HeartTimer::TimerHandler(const asio::error_code & ec)
	{
		if (ec)
		{

		}
		else
		{
			_timeoutFunc();
			_timer.expires_after(_timeoutValue);
			_timer.async_wait(std::bind(&HeartTimer::TimerHandler, this, _errCode));
		}
	}

}