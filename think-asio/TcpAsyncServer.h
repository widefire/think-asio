#pragma once

#include "asio.hpp"

#include <iostream>
#include <set>
#include "TcpAsyncClient.h"


namespace gra {

	class TcpAsyncServer
	{
	public:
		TcpAsyncServer();
		virtual ~TcpAsyncServer();
		bool StartServer(short port);
		bool StopServer();
		void SetLogger(FuncLogger funcLogger);
		void SetAccepted(FuncAcceptedClient funcAccepted);
	protected:
		asio::io_service _ioService;
	private:
		void InitServer();
		void DoAccept();
	private:
		bool _looping = false;
		std::thread _acceptorLoop;
		asio::ip::tcp::acceptor _acceptor;
		std::shared_ptr<TcpAsyncClient> _clientWait = nullptr;
		FuncLogger _logger;
		FuncAcceptedClient _acceptedClient;
	};
}


