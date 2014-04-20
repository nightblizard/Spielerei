#include <Poco/Net/DNS.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/ServerSocket.h>
#include "Network/TCPServer.h"
#include <Poco/Net/TCPServerParams.h>
#include "Network/TCPServerConnectionFactory.h"
#include "Network/TCPServerDispatcher.h"
#include <Poco/Logger.h>

#include "Types.h"
#include "Build.h"



using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;
#include <iostream>

#include <Poco/FileChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/SplitterChannel.h>

#include "Network/Session.h"

int main(int argc, char* argv[], char* options[])
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

	Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
//	pCons->setProperty("archive", "timestamp");

	Poco::AutoPtr<Poco::FileChannel> fileChannel(new Poco::FileChannel("Testing.log"));
	//fileChannel->setProperty("path", "Testing.log");
	fileChannel->setProperty("rotation", "daily");
	fileChannel->setProperty("archive", "timestamp");

	Poco::AutoPtr<Poco::SplitterChannel> splitterChannel(new Poco::SplitterChannel);
	splitterChannel->addChannel(pCons);
	splitterChannel->addChannel(fileChannel);


	Poco::Logger::root().setChannel(splitterChannel);
	auto& logger = Poco::Logger::get("Testing");
	
	logger.information("MyServer - Build: " + std::to_string(BUILD_NUMBER));
	logger.warning("Warning!!!");

	Poco::Net::ServerSocket svs(3724);

	auto* params = new Poco::Net::TCPServerParams();
	params->setMaxThreads(1);
	params->setMaxQueued(4);
	params->setThreadIdleTime(100);

	TCPServer server(new TCPServerConnectionFactoryImpl<Session>(), svs, params);
	server.start();




	for(;;)
	{
		std::cout << "Threads: " << server.currentThreads() << std::endl;
		Sleep(1000);
	}

	std::cin.get();
}