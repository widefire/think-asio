
#include <iostream>

#include "../think-asio/TcpAsyncServer.h"

using namespace gra;

int main(int argc, char **argv) {
	TcpAsyncServer svr;
	svr.StartServer(10000);

	std::string wait;
	std::cin >> wait;
	return 1;
}