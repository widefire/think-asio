#include <chrono>
#include "ForeverIOService.h"

namespace gra {

	ForeverIOService::ForeverIOService():
		_timer(_ioService)
	{
		_runing = std::move(std::thread(std::bind(&ForeverIOService::Runing, this)));
	}

	void ForeverIOService::Runing()
	{
		_timer.expires_after(std::chrono::hours(24*365*100));//100year
		_timer.async_wait([&](const asio::error_code &ec)
		{
			if (ec)
			{
				std::cout << ec.message();
			}
			else {
				std::cout << "must some error";
			}
		});
		_ioService.run();
	}


	asio::io_service & ForeverIOService::Get()
	{
		static ForeverIOService service;
		return service._ioService;
	}

	ForeverIOService::~ForeverIOService()
	{
		_ioService.stop();
		if (_runing.joinable())
		{
			_runing.join();
		}
	}
}

