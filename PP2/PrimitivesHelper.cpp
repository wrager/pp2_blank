#include "PrimitivesHelper.h"
#include <memory>

namespace
{
void* CreatePrimitive(SynchranizationPrimitivesType type)
{
	void * primitive = nullptr;
	switch (type)
	{
	case SynchranizationPrimitivesType::Mutex:
		primitive = CreateMutex(NULL, false, NULL);
		break;
	case SynchranizationPrimitivesType::Semaphore:
		primitive = CreateSemaphore(NULL, 1, 1, NULL);
		break;
	case SynchranizationPrimitivesType::Event:
		primitive = CreateEvent(NULL, false, true, NULL);
		break;
	case SynchranizationPrimitivesType::CriticalSection:
		InitializeCriticalSection((LPCRITICAL_SECTION)primitive);
		break;
	}
	return primitive;
}
}

CPrimitivesHelper::CPrimitivesHelper(SynchranizationPrimitivesType type)
	: m_primitiveType(type)
	, m_primitive(std::move(CreatePrimitive(type)))
{
}

void CPrimitivesHelper::EnterPrimitiveZone()
{
	switch (m_primitiveType)
	{
	case SynchranizationPrimitivesType::CriticalSection:
		EnterCriticalSection((LPCRITICAL_SECTION)m_primitive);
		break;
	default:
		WaitForSingleObject(m_primitive, INFINITE);
		break;
	}
}

void CPrimitivesHelper::LeavePrimitiveZone()
{
	switch (m_primitiveType)
	{
	case SynchranizationPrimitivesType::Mutex:
		LeaveCriticalSection((LPCRITICAL_SECTION)m_primitive);
		break;
	case SynchranizationPrimitivesType::Semaphore:
		ReleaseSemaphore(m_primitive, 1, NULL);
		break;
	case SynchranizationPrimitivesType::Event:
		ReleaseMutex(m_primitive);
		break;
	case SynchranizationPrimitivesType::CriticalSection:
		SetEvent(m_primitive);
		break;
	}
}