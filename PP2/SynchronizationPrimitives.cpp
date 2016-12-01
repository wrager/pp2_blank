#include "stdafx.h"
#include "SynchronizationPrimitives.h"

PrimitivesCollection::PrimitivesCollection(PrimitiveType type)
{
	if (type == PrimitiveType::Mutex)
	{
		mutex = CreateMutex(NULL, false, NULL);
	}
	else if (type == PrimitiveType::Mutex)
	{
		semaphore = CreateSemaphore(NULL, 1, 1, NULL);
	}
	else if (type == PrimitiveType::Event)
	{
		event = CreateEvent(NULL, false, true, NULL);
	}
	else if (type == PrimitiveType::CriticalSection)
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
	else if (event)
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
	else if (event)
	{
		SetEvent(event.get());
	}
}
