
#include <iostream>

#include "../think-asio/TcpAsyncServer.h"
#include "../think-asio/ForeverIOService.h"

using namespace gra;

int main(int argc, char **argv) {
	std::mutex mux;
	std::lock_guard<std::mutex> guard(mux);
	auto ret = mux.try_lock();
	TcpAsyncServer svr;
	svr.StartServer(10000);
	auto &forever=ForeverIOService::Get();
	std::string wait;
	std::cin >> wait;
	//svr.StopServer();
	return 1;
}