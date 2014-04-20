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


#include "Session.h"



Session::Session(const Poco::Net::StreamSocket& socket) :
TCPServerConnection(socket)
{
}

void Session::run()
{
	std::cout << "New connection from: " << socket().peerAddress().host().toString() << std::endl;

	bool isOpen = true;
	Poco::Timespan timeout(10, 0);
	unsigned char incommingBuffer[1000];

	while (isOpen)
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
			} catch (Poco::Exception& exc)
			{
				std::cerr << "Network error: " << exc.displayText() << std::endl;
				_alive = false;
				isOpen = false;
			}

			if (numBytes == 0)
			{
				std::cout << "Client closes connection!" << std::endl;
				_alive = false;
				isOpen = false;
			} else
			{
				std::cout << "Receiving numBytes: " << numBytes << std::endl;

				char* name = ((char*)(incommingBuffer + 4));
				std::cout << name << std::endl;
			}
		}
	}

	std::cout << "Connection finished!" << std::endl;
}