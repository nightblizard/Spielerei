#include <Poco/Net/DNS.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerParams.h>
#include <Poco/Net/TCPServerConnectionFactory.h>

using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;
#include <iostream>

class Session : public Poco::Net::TCPServerConnection
{
public:
	Session(const Poco::Net::StreamSocket& socket) :
		Poco::Net::TCPServerConnection(socket)
	{
	}

	void run() override
	{
		std::cout << "New connection from: " << socket().peerAddress().host().toString() << std::endl;

		bool isOpen = true;
		Poco::Timespan timeout(10, 0);
		unsigned char incommingBuffer[1000];

		while(isOpen)
		{
			if (socket().poll(timeout, Poco::Net::Socket::SELECT_READ) == false)
				std::cout << "TIMEOUT!" << std::endl;
			else
			{
				std::cout << "RX EVENT!!! --->";
				int numBytes = 0;

				try
				{
					numBytes = socket().receiveBytes(incommingBuffer, sizeof(incommingBuffer));
				}
				catch(Poco::Exception& exc)
				{
					std::cerr << "Network error: " << exc.displayText() << std::endl;
					isOpen = false;
				}

				if (numBytes == 0)
				{
					std::cout << "Client closes connection!" << std::endl;
					isOpen = false;
				} else
				{
					std::cout << "Receiving numBytes: " << numBytes << std::endl;

					char* name = ((char*)(incommingBuffer + 4));
					std::cout << name << std::endl;
					isOpen = false;
				}
			}
		}

		std::cout << "Connection finished!" << std::endl;
	}
};



int main()
{
	/*
	auto entry = DNS::hostByName("www.google.de");
	std::cout << "Canonical Name: " << entry.name() << std::endl;

	auto aliases = entry.aliases();

	for(auto& alias : aliases)
		std::cout << "Alias: " << alias << std::endl;

	auto addresses = entry.addresses();

	for (auto& address : addresses)
		std::cout << "Address: " << address.toString() << std::endl;
	*/
	/*
	Poco::Net::SocketAddress socketAddress("www.appinf.com", 80);
	Poco::Net::StreamSocket socket(socketAddress);
	Poco::Net::SocketStream socketStream(socket);

	socketStream << "GET / HTTP/1.1\r\n"
					"Host: www.appinf.com\r\n"
					"\r\n";

	socketStream.flush();

	Poco::StreamCopier::copyStream(socketStream, std::cout);*/

	Poco::Net::ServerSocket svs(3724);

	auto* params = new Poco::Net::TCPServerParams();
	params->setMaxThreads(4);
	params->setMaxQueued(4);
	params->setThreadIdleTime(100);

	Poco::Net::TCPServer server(new Poco::Net::TCPServerConnectionFactoryImpl<Session>(), svs, params);
	server.start();

	for(;;)
	{
		std::cout << "Threads: " << server.currentThreads() << std::endl;
		Sleep(1000);
	}

	std::cin.get();
}