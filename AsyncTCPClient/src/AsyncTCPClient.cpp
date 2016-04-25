//============================================================================
// Name        : AsyncTCPClient.cpp
// Author      : Sihyung Lee
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TCPClient.h"

#define DEFAULT_TARGET_IP "127.0.0.1"
#define DEFAULT_PORT 31400

using namespace std;

typedef struct _userInput {
	int nRepeat = 0;
	std::string strTargetIP = DEFAULT_TARGET_IP;
	int nPort = DEFAULT_PORT;
} UserInput;

void help()
{
    cout << "Usage: ./AsyncTCPClient [OPTION]" << endl;
    cout << " -h Help" << endl;
    cout << " -v Version" << endl;
    cout << " -r Repeat count" << endl;
    cout << " -t Target IP" << endl;
    cout << " -p Port" << endl;
    exit(0);
}

void version()
{
	cout << "Version : 0.1" << endl;
    exit(0);
}

int main(int argc, char** argv) {
	int opt;
	UserInput userInput;
	while((opt = getopt(argc, argv, "hvr:t:p:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				help();
				break;
			case 'v':
				version();
				break;
			case 'r':
				userInput.nRepeat = atoi(optarg);
				userInput.nRepeat = ( userInput.nRepeat < 0) ? 0 : userInput.nRepeat;

				break;
			case 't':
				userInput.strTargetIP = optarg;
				break;
			case 'p':
				userInput.nPort = atoi(optarg);
				userInput.nPort = ( userInput.nPort < 0) ? DEFAULT_PORT : userInput.nPort;
				break;
			case '?':
				if (optopt == 'c')
				  fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
				  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
				  fprintf (stderr,
						   "Unknown option character `\\x%x'.\n",
						   optopt);
				return 1;
		    default:
		        abort ();
		}
	}

	cout << " * Repeat count : " << userInput.nRepeat << endl;
	cout << " * Target IP count : " << userInput.strTargetIP << endl;
	cout << " * Port count : " << userInput.nPort << endl;

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(userInput.strTargetIP), userInput.nPort);

	TCPClient client(io_service);
	client.Connect(endpoint);
	io_service.run();

	std::cout << "Disconneted" << std::endl;
	getchar();

	return 0;
}
