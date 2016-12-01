#pragma once
#include <boost/optional.hpp>
#include <Windows.h>
#include "PrimitiveType.h"

class PrimitivesCollection
{
public:
	PrimitivesCollection(PrimitiveType type);
	~PrimitivesCollection();

	void EnterPrimitiveZone();
	void LeavePrimitiveZone();

private:
	boost::optional<HANDLE> mutex;
	boost::optional<HANDLE> semaphore;
	boost::optional<HANDLE> event;
	boost::optional<CRITICAL_SECTION> criticalSection;
};