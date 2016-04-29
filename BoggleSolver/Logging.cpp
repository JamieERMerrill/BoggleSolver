#include "stdafx.h"
#include "Logging.h"
#include <iostream>
#include <stdarg.h>

const int kArbitraryMaxLogLength = 1024;

void writeLog(const char* message)
{
	std::cout << message;
}

void writeLogLine(const char* message)
{
	std::cout << message << std::endl;
}

void writeLogLineFormatted(const char* message, ...)
{
	char writeBuffer[kArbitraryMaxLogLength];
	va_list args;
	va_start(args, message);
	vsprintf_s(writeBuffer, message, args);
	va_end(args);
	std::cout << writeBuffer << std::endl;
}
