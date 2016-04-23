/*
 * Session.h
 *
 *  Created on: Apr 23, 2016
 *      Author: sihyung
 */

#ifndef SESSION_H_
#define SESSION_H_

#include <iostream>
#include <string>
#include <boost/asio.hpp>

#define MAX_MSG 1024

class Session {
public:
	Session(boost::asio::io_service& io_service)
		: m_Socket(io_service) {
	}
	virtual ~Session() {}

	boost::asio::ip::tcp::socket& Socket();
	void PostReceive();

private:
	void handle_write(const boost::system::error_code& /*error*/, size_t /*byte_transferred*/);
	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);

	boost::asio::ip::tcp::socket m_Socket;
	std::string m_WriteMessage;
	char m_szReceiveBuffer[MAX_MSG];
};

#endif /* SESSION_H_ */
