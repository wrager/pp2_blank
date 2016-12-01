#include "stdafx.h"
#include "StreamHandler.h"

PrimitiveType CStreamHandler::GetPrimitiveType(const std::string & cmdArguments)
{
	PrimitiveType type = PrimitiveType::None;

	if (cmdArguments == "mutex")
	{
		type = PrimitiveType::Mutex;
	}
	else if (cmdArguments == "semaphore")
	{
		type = PrimitiveType::Semaphore;
	}
	else if (cmdArguments == "event")
	{
		type = PrimitiveType::Event;
	}
	else if (cmdArguments == "critical_section")
	{
		type = PrimitiveType::CriticalSection;
	}

	return type;
}
