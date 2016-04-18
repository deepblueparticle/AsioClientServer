//============================================================================
// Name        : AsynTCPServer.cpp
// Author      : Sihyung Lee
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

const unsigned short PORT_NUMBER = 31400;

class Session {
public:
	Session(boost::asio::io_service& io_service)
		: m_Socket(io_service) {
	}

	boost::asio::ip::tcp::socket& Socket() {
		return m_Socket;
	}

	void PostReceive() {
		memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));
		m_Socket.async_read_some (
				boost::asio::buffer(m_ReceiveBuffer),
				boost::bind(&Session::handle_receive, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));

	}

private:
	void handle_write(const boost::system::error_code& /*error*/, size_t /*byte_transferred*/) {
	}

	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
		if( error ) {
			if( error == boost::asio::error::eof ) {
				std::cout << " Disconnected " << std::endl;
			} else {
				std::cout << " Error no : " << error.value() << " error Message : " << error.message() << std::endl;
			}
		} else {
			const std::string strRecvMessage = m_ReceiveBuffer.data();
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

	boost::asio::ip::tcp::socket m_Socket;
	std::string m_WriteMessage;
	std::array<char, 128> m_ReceiveBuffer;
};

class TCP_Server {
public:
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

private:
	void StartAccept() {
		std::cout << "Wating for the client...." << std::endl;
		m_pSession = new Session(m_acceptor.get_io_service());

		m_acceptor.async_accept(m_pSession->Socket(),
				boost::bind(&TCP_Server::handle_accept,
						this, m_pSession, boost::asio::placeholders::error));
	}

	void handle_accept(Session* pSession, const boost::system::error_code& error) {
		if(!error) {
			std::cout << "Connected" << std::endl;
			pSession->PostReceive();
		}
	}

	int m_nSeqNumber;
	boost::asio::ip::tcp::acceptor m_acceptor;
	Session* m_pSession;

};



int main() {
	boost::asio::io_service io_service;
	TCP_Server server(io_service);
	io_service.run();

	std::cout << "Disconnected" << std::endl;
	getchar();

	return 0;
}
