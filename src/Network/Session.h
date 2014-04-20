#pragma once

#include "TCPServerConnection.h"


class Session : public TCPServerConnection
{
public:
	Session(const Poco::Net::StreamSocket& socket) :
		TCPServerConnection(socket)
	{
	}

	void run() override
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
};