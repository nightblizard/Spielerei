//
// TCPServerConnectionFactory.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/TCPServerConnectionFactory.h#1 $
//
// Library: Net
// Package: TCPServer
// Module:  TCPServerConnectionFactory
//
// Definition of the TCPServerConnectionFactory class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#pragma once

#include <Poco/Net/Net.h>
#include "TCPServerConnection.h"
#include <Poco/SharedPtr.h>


class Net_API TCPServerConnectionFactory
	/// A factory for TCPServerConnection objects.
	///
	/// The TCPServer class uses a TCPServerConnectionFactory
	/// to create a connection object for each new connection
	/// it accepts.
	///
	/// Subclasses must override the createConnection()
	/// method.
	///
	/// The TCPServerConnectionFactoryImpl template class
	/// can be used to automatically instantiate a
	/// TCPServerConnectionFactory for a given subclass
	/// of TCPServerConnection.
{
public:
	typedef Poco::SharedPtr<TCPServerConnectionFactory> Ptr;

	virtual ~TCPServerConnectionFactory();
	/// Destroys the TCPServerConnectionFactory.

	virtual TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket) = 0;
	/// Creates an instance of a subclass of TCPServerConnection,
	/// using the given StreamSocket.

protected:
	TCPServerConnectionFactory();
	/// Creates the TCPServerConnectionFactory.

private:
	TCPServerConnectionFactory(const TCPServerConnectionFactory&);
	TCPServerConnectionFactory& operator = (const TCPServerConnectionFactory&);
};


template <class S>
class TCPServerConnectionFactoryImpl : public TCPServerConnectionFactory
	/// This template provides a basic implementation of
	/// TCPServerConnectionFactory.
{
public:
	TCPServerConnectionFactoryImpl()
	{
	}

	~TCPServerConnectionFactoryImpl()
	{
	}

	TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
	{
		return new S(socket);
	}
};