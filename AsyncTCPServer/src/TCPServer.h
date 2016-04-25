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
