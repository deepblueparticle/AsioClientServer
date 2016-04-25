/*
 * TCPClient.h
 *
 *  Created on: Apr 25, 2016
 *      Author: sihyung
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include <iostream>
#include <boost/asio.hpp>

#define MAX_MSG 1024

class TCPClient {
public:
	TCPClient(boost::asio::io_service& io_service);
	virtual ~TCPClient();

	void Connect(boost::asio::ip::tcp::endpoint& endpoint);

private:
	void PostWrite();
	void PostReceive();
	void handle_connect(const boost::system::error_code& error);
	void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);
	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);

	boost::asio::io_service& m_io_service;
	boost::asio::ip::tcp::socket m_Socket;
	int m_nSeqNumber;
	char m_szReceiveBuffer[MAX_MSG];
	std::string m_WriteMessage;
};


#endif /* TCPCLIENT_H_ */
