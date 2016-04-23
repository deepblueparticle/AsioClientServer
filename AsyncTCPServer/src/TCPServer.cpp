/*
 * TCPServer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: sihyung
 */

#include "TCPServer.h"
#include <boost/bind.hpp>

const unsigned short PORT_NUMBER = 31400;

TCPServer::TCPServer(boost::asio::io_service& io_service)
	: m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER)) {
		m_pSession = nullptr;
		StartAccept();
	}

TCPServer::~TCPServer() {
	if( m_pSession != nullptr ) {
		delete m_pSession;
	}
}

void TCPServer::StartAccept() {
	std::cout << "Wating for the client...." << std::endl;
	m_pSession = new Session(m_acceptor.get_io_service());

	m_acceptor.async_accept(m_pSession->Socket(),
			boost::bind(&TCPServer::handle_accept,
					this, m_pSession, boost::asio::placeholders::error));
}

void TCPServer::handle_accept(Session* pSession, const boost::system::error_code& error) {
	if(!error) {
		std::cout << "Connected" << std::endl;
		pSession->PostReceive();
	}
}
