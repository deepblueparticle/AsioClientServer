/*
 * TCPClient.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: sihyung
 */

#include "TCPClient.h"
#include <boost/bind.hpp>

TCPClient::TCPClient(boost::asio::io_service& io_service)
: m_io_service(io_service),
  m_Socket(io_service),
  m_nSeqNumber(0) {
}

TCPClient::~TCPClient() {
	// TODO Auto-generated destructor stub
}

void TCPClient::Connect(boost::asio::ip::tcp::endpoint& endpoint) {
	m_Socket.async_connect(endpoint, boost::bind(&TCPClient::handle_connect, this, boost::asio::placeholders::error));
}

void TCPClient::PostWrite() {
	if(m_Socket.is_open() == false) {
		return;
	}

	if(m_nSeqNumber > 7) {
		m_Socket.close();
		return;
	}

	++m_nSeqNumber;

	char szMessage[128] = {0,};
	snprintf(szMessage, 128-1, "%d - Send Message", m_nSeqNumber);

	m_WriteMessage = szMessage;

	boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
			boost::bind(&TCPClient::handle_write, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)
	);

	PostReceive();
}

void TCPClient::PostReceive() {
	memset(m_szReceiveBuffer, 0, MAX_MSG);
	m_Socket.async_read_some(boost::asio::buffer(m_szReceiveBuffer),
			boost::bind(&TCPClient::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}

void TCPClient::handle_connect(const boost::system::error_code& error) {
	if(error) {
		std::cout << "connect failed : " << error.message() << std::endl;
	} else {
		std::cout << "conncted" << std::endl;
		PostWrite();
	}
}

void TCPClient::handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) {

}

void TCPClient::handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
	if(error) {
		if(error ==  boost::asio::error::eof) {
			std::cout << "Disconnected" << std::endl;
		} else {
			std::cout << "error no: " << error.value() << " error Message: " << error.message() << std::endl;
		}
	} else {
		const std::string strRecvMessage = m_szReceiveBuffer;
		std::cout << "Message from server: " << strRecvMessage << ", size : " << bytes_transferred << std::endl;
		PostWrite();
	}
}

