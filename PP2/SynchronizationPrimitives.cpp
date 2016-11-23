#include "stdafx.h"
#include "SynchronizationPrimitives.h"

PrimitivesCollection::PrimitivesCollection(const std::string & type)
{
	if (type == "mutex")
	{
		mutex = CreateMutex(NULL, false, NULL);
	}
	else if (type == "semaphore")
	{
		semaphore = CreateSemaphore(NULL, 1, 1, NULL);
	}
	else if (type == "event")
	{
		event = CreateEvent(NULL, false, true, NULL);
	}
	else if (type == "critical_section")
	{
		InitializeCriticalSection(&criticalSection.get());
	}
}

PrimitivesCollection::~PrimitivesCollection()
{
	if(criticalSection)
	{
		DeleteCriticalSection(&criticalSection.get());
	}
}

void PrimitivesCollection::EnterPrimitiveZone()
{
	if (criticalSection)
	{
		EnterCriticalSection(&criticalSection.get());
	}
	else if (semaphore)
	{
		WaitForSingleObject(semaphore.get(), INFINITE);
	}
	else if (mutex)
	{
		WaitForSingleObject(mutex.get(), INFINITE);
	}
	else if (event.get())
	{
		WaitForSingleObject(event.get(), INFINITE);
	}
}

void PrimitivesCollection::LeavePrimitiveZone()
{
	if (criticalSection)
	{
		LeaveCriticalSection(&criticalSection.get());
	}
	else if (semaphore)
	{
		ReleaseSemaphore(semaphore.get(), 1, NULL);
	}
	else if (mutex)
	{
		ReleaseMutex(mutex.get());
	}
	else if (event.get())
	{
		SetEvent(event.get());
	}
}
