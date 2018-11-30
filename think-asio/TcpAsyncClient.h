#pragma once

#include <iostream>
#include <vector>
#include <queue>

#include "asio.hpp"


namespace gra {
	class TcpAsyncClient;

	typedef std::shared_ptr<std::vector<uint8_t>> PtrBuf;
	typedef std::function<void(std::shared_ptr<TcpAsyncClient>)> FuncAcceptedClient;
	typedef std::function<void(std::string)> FuncLogger;
	typedef std::function<void(const asio::error_code& error, std::size_t n)> FuncWriteComplete;
	typedef std::function<void(const asio::error_code& error,std::size_t bytes_transferred)> FuncReadComplete;


	class TcpAsyncClient:public std::enable_shared_from_this<TcpAsyncClient>
	{
	public:
		static std::shared_ptr<TcpAsyncClient> CreateServerClient(
			asio::io_service& ioService
		);
		static std::shared_ptr<TcpAsyncClient> CreateClient(
			asio::io_service& ioService,
			std::string addr,
			short port,
			std::string &ec
		);
		virtual ~TcpAsyncClient();
		asio::ip::tcp::socket &Socket();
		bool Write(PtrBuf data,FuncWriteComplete callback);
		bool Read(PtrBuf buf, FuncReadComplete callback);
		bool DecreaseAsyncCallback();
		int  AsyncCount();
	private:
		TcpAsyncClient(asio::io_service& ioService);
		void PostWrite();
		void PostRead();
	protected:
		asio::io_service& _ioService;
		std::mutex _mux;
		asio::ip::tcp::socket _socket;
		bool _isOpen = true;
		bool _isAcceptedClient = false;

		std::queue<std::pair<PtrBuf, FuncWriteComplete>>  _writeQueue;
		std::queue<std::pair<PtrBuf, FuncReadComplete>>  _readQueue;
		int _asyncCount = 0;
		//for acceped client

		//for !acceped client
		std::string _addr = "";
		short _port = -1;
	};


}

