#pragma once
#include <Windows.h>
#include "SynchronizationPrimitivesType.h"

template <typename PrimitiveType>
struct PrimitiveContainer
{
	PrimitiveType primitive;
};

class CPrimitivesHelper
{
public:
	CPrimitivesHelper(SynchranizationPrimitivesType type);
	void EnterPrimitiveZone();
	void LeavePrimitiveZone();

private:
	SynchranizationPrimitivesType m_primitiveType;
	void * m_primitive;
};