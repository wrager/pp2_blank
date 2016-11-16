#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "CBankClient.h"

enum class idPrimitive
{
		CriticalSection = 0
	,	Mutex
	,	Semaphore
	,	Event
};

class CBankClient;

class CBank
{
public:
	CBank(idPrimitive idPrimitiveType);
	~CBank();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	CBankClient *					CreateClient();
	void							UpdateClientBalance(size_t index, int value);
	void							UpdateClientBalance(CBankClient& client, int value);

	void							CreateThreads(size_t amountCpu);
	void							ResumeThreads();

	int								GetTotalBalance();

private:
	void							UpdateTotalBalance(int value);
	void							SomeLongOperations();
	unsigned int					GetSleepDuration();
	int								GetAffinityMask(size_t amountThread, size_t threadIndex);

	bool							EnableSynchronizationPrimitive(CBankClient &client);
	void							DisableSynchronizationPrimitive();

//////////////////////////////////////////////////////////////////////
// Data
private:
	union
	{
		CRITICAL_SECTION				m_criticalSection;
		HANDLE							m_hMutex;
		HANDLE							m_hSemaphore;
		HANDLE							m_hEvent;
	};
	idPrimitive						m_idPrimitive;
	HANDLE							m_pauseEvent;

	size_t							m_amountCpu = 1;
	std::vector<CBankClient>		m_clients;
	std::vector<HANDLE>				m_threads;
	int								m_totalBalance = 100;

	bool							m_isUpdate = false;
	size_t							m_randomIndex = 0;

	
};