#pragma once
#include <map>

enum class SynchranizationPrimitivesType
{
	CriticalSection,
	Mutex,
	Semaphore,
	Event,
	None
};

static const std::map<std::string, SynchranizationPrimitivesType> PRIMITIVES_MAP = {
	{"CriticalSection", SynchranizationPrimitivesType::CriticalSection},
	{"Mutex", SynchranizationPrimitivesType::Mutex},
	{"Semaphore", SynchranizationPrimitivesType::Semaphore},
	{"Event", SynchranizationPrimitivesType::Event},
	{"None", SynchranizationPrimitivesType::None}
};