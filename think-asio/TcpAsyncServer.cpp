#include "TcpAsyncServer.h"

namespace gra {

	using namespace asio;
	using namespace std;

	TcpAsyncServer::TcpAsyncServer()
		:_acceptor(_ioService)
	{
		InitServer();
	}


	TcpAsyncServer::~TcpAsyncServer()
	{
	}
	bool TcpAsyncServer::StartServer(short port)
	{

		if (_looping) {
			return false;
		}
		_looping = true;


		auto funcLoop = [&]() {
			auto endpoint = ip::tcp::endpoint(ip::tcp::v4(), port);
			_acceptor = ip::tcp::acceptor(_ioService, endpoint);

			this->DoAccept();

			this->_ioService.run();
		};

		this->_acceptorLoop = std::move(
			std::thread(funcLoop)
		);


		return true;
	}
	bool TcpAsyncServer::StopServer()
	{
		if (!_looping) {
			return true;
		}

		_ioService.stop();
		if (this->_acceptorLoop.joinable())
		{
			this->_acceptorLoop.join();
		}
		_looping = false;
		return true;
	}
	void TcpAsyncServer::SetLogger(FuncLogger funcLogger)
	{
		if (funcLogger != nullptr){
			_logger = funcLogger;
		}
	}
	void TcpAsyncServer::SetAccepted(FuncAcceptedClient funcAccepted)
	{
		if (funcAccepted != nullptr) {
			_acceptedClient = funcAccepted;
		}
	}
	void TcpAsyncServer::InitServer()
	{
		_logger = [&](std::string param) {
			cout << param << endl;
		};

		_acceptedClient = [&](std::shared_ptr<TcpAsyncClient>)
		{};

	}
	void TcpAsyncServer::DoAccept()
	{
		_clientWait = TcpAsyncClient::CreateServerClient(
			this->_ioService
		);

		_acceptor.async_accept(_clientWait->Socket(),
			[&](const error_code &ec)
		{
			if (ec) {
				std::string strEc;
				strEc += __FILE__;
				strEc += __LINE__;
				strEc += ec.message();
				_logger(strEc);
			}
			else {
				_acceptedClient(_clientWait);
			}
			DoAccept();
		});
	}
}

