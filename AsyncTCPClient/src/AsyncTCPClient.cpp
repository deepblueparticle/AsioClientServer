//============================================================================
// Name        : AsyncTCPClient.cpp
// Author      : Sihyung Lee
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TCPClient.h"

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

int main() {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);

	TCPClient client(io_service);
	client.Connect(endpoint);
	io_service.run();

	std::cout << "Disconneted" << std::endl;
	getchar();

	return 0;
}
