/*
The MIT License (MIT)

Copyright (c) 2014 nightblizard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

void initLogger()
{
	Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);

	Poco::AutoPtr<Poco::FileChannel> fileChannel(new Poco::FileChannel("Testing.log"));
	fileChannel->setProperty("rotation", "daily");
	fileChannel->setProperty("archive", "timestamp");

	Poco::AutoPtr<Poco::SplitterChannel> splitterChannel(new Poco::SplitterChannel);
	splitterChannel->addChannel(pCons);
	splitterChannel->addChannel(fileChannel);

	gLog.setChannel(splitterChannel);
}

int main(int argc, char* argv[], char* options[])
{
	initLogger();

	gLog.information("MyServer - Build: " + std::to_string(BUILD_NUMBER));

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