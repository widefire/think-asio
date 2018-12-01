#pragma once

#include "asio.hpp"
#include <iostream>

namespace gra
{
	class TcpSyncHelper
	{
	public:
		TcpSyncHelper();
		~TcpSyncHelper();
		static std::shared_ptr<asio::ip::tcp::socket> CreateSocket(std::string addr, uint16_t port,std::string& err);
	};

}

