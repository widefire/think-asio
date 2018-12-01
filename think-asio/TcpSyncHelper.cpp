#include "TcpSyncHelper.h"
#include "ForeverIOService.h"

namespace gra
{

	TcpSyncHelper::TcpSyncHelper()
	{
	}


	TcpSyncHelper::~TcpSyncHelper()
	{
	}

	std::shared_ptr<asio::ip::tcp::socket> TcpSyncHelper::CreateSocket(std::string addr, uint16_t port, std::string & err)
	{
		auto socket = std::make_shared<asio::ip::tcp::socket>(ForeverIOService::Get());
		asio::error_code errorCode;
		asio::ip::tcp::resolver resolver(ForeverIOService::Get());
		auto strPort = std::to_string(port);
		auto epit = resolver.resolve({ addr, strPort });
		asio::connect(
			*socket,
			epit,
			errorCode
		);

		if (errorCode)
		{
			err = errorCode.message();
			return nullptr;
		}
		return socket;
	}

}
