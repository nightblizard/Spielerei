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

#pragma once

#include <Poco/Types.h>

typedef Poco::UInt8 uint8;
typedef Poco::Int8 int8;
typedef Poco::UInt16 uint16;
typedef Poco::Int16 int16;
typedef Poco::UInt32 uint32;
typedef Poco::Int32 int32;
typedef Poco::UInt64 uint64;
typedef Poco::Int64 int64;

typedef Poco::IntPtr intPtr;
typedef Poco::UIntPtr uintPtr;


#define gLog Poco::Logger::root()