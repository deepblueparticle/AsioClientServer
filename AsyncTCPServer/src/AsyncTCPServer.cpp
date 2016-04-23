//============================================================================
// Name        : AsynTCPServer.cpp
// Author      : Sihyung Lee
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPServer.h"

int main() {
	boost::asio::io_service io_service;
	TCPServer server(io_service);
	io_service.run();

	std::cout << "Disconnected" << std::endl;
	getchar();

	return 0;
}
