
#include <iostream>

#include "../think-asio/TcpAsyncServer.h"
#include "../think-asio/ForeverIOService.h"

using namespace gra;

int main(int argc, char **argv) {
	TcpAsyncServer svr;
	svr.StartServer(10000);
	auto &forever=ForeverIOService::Get();
	std::string wait;
	std::cin >> wait;
	//svr.StopServer();
	return 1;
}