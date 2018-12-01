#pragma once

#include <iostream>
#include "asio.hpp"

namespace gra {

	class ForeverIOService
	{
	public:
		static asio::io_service& Get();
		~ForeverIOService();
	private:
		ForeverIOService();
		void Runing();
	private:
		asio::io_service _ioService;
		std::thread _runing;
		asio::steady_timer _timer;
	};
}


