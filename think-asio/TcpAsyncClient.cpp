#include "TcpAsyncClient.h"

namespace gra {

	TcpAsyncClient::TcpAsyncClient(asio::io_service& ioService)
		:
		_ioService(ioService)
		,_socket(ioService)
	{
	}

	void TcpAsyncClient::PostWrite()
	{
		std::lock_guard<std::mutex> guard(_mux);
		while (_writeQueue.size()>0)
		{
			auto &pair = _writeQueue.front();
			asio::async_write(_socket, asio::buffer(*pair.first), pair.second);
			_writeQueue.pop();
		}
	}

	void TcpAsyncClient::PostRead()
	{
		std::lock_guard<std::mutex> guard(_mux);
		while (_readQueue.size()>0)
		{
			auto &pair = _readQueue.front();
			asio::async_read(_socket, asio::buffer(*pair.first),
				pair.second);
			_readQueue.pop();
		}
	}


	std::shared_ptr<TcpAsyncClient> TcpAsyncClient::CreateServerClient(
		asio::io_service& ioService)
	{
		auto ptr = new TcpAsyncClient(ioService);
		std::shared_ptr<TcpAsyncClient> client(ptr);
		client->_isAcceptedClient = true;

		return client;
	}

	std::shared_ptr<TcpAsyncClient> TcpAsyncClient::CreateClient(
		asio::io_service& ioService, std::string addr, short port,
		std::string &ec)
	{
		auto ptr = new TcpAsyncClient(ioService);
		std::shared_ptr<TcpAsyncClient> client(ptr);
		client->_isAcceptedClient = false;
		client->_addr = addr;
		client->_port = port;

		asio::error_code errorCode;
		asio::ip::tcp::resolver resolver(client->_ioService);
		auto strPort = std::to_string(port);
		auto epit = resolver.resolve({ addr, strPort });
		asio::connect(
			client->_socket,
			epit,
			errorCode
		);

		if (errorCode)
		{
			ec = errorCode.message();
			return nullptr;
		}

		return client;
	}

	TcpAsyncClient::~TcpAsyncClient()
	{
	}
	asio::ip::tcp::socket & TcpAsyncClient::Socket()
	{
		return this->_socket;

	}

	bool TcpAsyncClient::Write(PtrBuf data, FuncWriteComplete callback)
	{
		if (!_isOpen)
		{
			return false;
		}

		std::lock_guard<std::mutex> guard(_mux);
		_writeQueue.push(std::make_pair(data, callback));

		_ioService.post(std::bind(&TcpAsyncClient::PostWrite, this));

		return true;
	}

	bool TcpAsyncClient::Read(PtrBuf buf, FuncReadComplete callback)
	{
		if (!_isOpen)
		{
			return false;
		}

		std::lock_guard<std::mutex> guard(_mux);
		_readQueue.push(std::make_pair(buf, callback));

		_ioService.post(std::bind(&TcpAsyncClient::PostRead, this));

		return true;
	}

}

