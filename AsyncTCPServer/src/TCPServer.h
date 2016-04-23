/*
 * TCPServer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: sihyung
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <iostream>
#include "Session.h"


class TCPServer {
public:
	TCPServer(boost::asio::io_service& io_service);
	virtual ~TCPServer();
private:
	void StartAccept();
	void handle_accept(Session* pSession, const boost::system::error_code& error);

	int m_nSeqNumber;
	boost::asio::ip::tcp::acceptor m_acceptor;
	Session* m_pSession;

};

#endif /* TCPSERVER_H_ */





/*
	TCP_Server(boost::asio::io_service& io_service)
	: m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER)) {
		m_pSession = nullptr;
		StartAccept();
	}

	~TCP_Server() {
		if( m_pSession != nullptr ) {
			delete m_pSession;
		}
	}
*/
