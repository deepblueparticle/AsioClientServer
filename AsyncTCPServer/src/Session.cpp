/*
 * Session.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: sihyung
 */

#include "Session.h"
#include <boost/bind.hpp>

boost::asio::ip::tcp::socket& Session::Socket() {
	return m_Socket;
}

void Session::PostReceive() {
	memset(m_szReceiveBuffer, 0, MAX_MSG);
	m_Socket.async_read_some (
			boost::asio::buffer(m_szReceiveBuffer, MAX_MSG),
			boost::bind(&Session::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)
	);
}

void Session::handle_write(const boost::system::error_code& /*error*/, size_t /*byte_transferred*/) {
}

void Session::handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
	if( error ) {
		if( error == boost::asio::error::eof ) {
			std::cout << " Disconnected " << std::endl;
		} else {
			std::cout << " Error no : " << error.value() << " error Message : " << error.message() << std::endl;
		}
	} else {
		const std::string strRecvMessage = m_szReceiveBuffer;
		std::cout << " Message from client : " << strRecvMessage << ", size : " << bytes_transferred << std::endl;
			char szMessage[128] = {0,};
		snprintf(szMessage, 128-1 , "Re:%s", strRecvMessage.c_str());
		m_WriteMessage = szMessage;
			boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
				boost::bind(&Session::handle_write, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			PostReceive();
	}
}
