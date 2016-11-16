#include "CBank.h"
#include "stdafx.h"

CBank::CBank(idPrimitive idPrimitiveType)
{
	m_idPrimitive = idPrimitiveType;
	switch (m_idPrimitive)
	{
	case idPrimitive::CriticalSection:
		InitializeCriticalSection(&m_criticalSection);
		break;
		// @param first parametr - SECURITY_ATTRIBUTE
	case idPrimitive::Mutex:
		// second parametr -  thread use the mutex 
		m_hMutex = CreateMutex(NULL, false, NULL);
		break;
	case idPrimitive::Semaphore:
		// second and third - range amount active thread
		m_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		break;
	case idPrimitive::Event:
		/*
		bManualReset

		If this parameter is TRUE, the function creates a manual-reset
		event object, which requires the use of the ResetEvent function 
		to set the event state to nonsignaled. If this parameter is
		FALSE, the function creates an auto-reset event object, and 
		system automatically resets the event state to nonsignaled
		after a single waiting thread has been released.

		bInitialState

		If this parameter is TRUE, the initial state of the event
		object is signaled; otherwise, it is nonsignaled.
		*/
		m_hEvent = CreateEvent(NULL, true , true, NULL);
		m_pauseEvent = CreateEvent(NULL, false, false, NULL);
		break;
	default:
		break;
	}
}

CBank::~CBank()
{
	switch (m_idPrimitive)
	{
	case idPrimitive::CriticalSection:
		DeleteCriticalSection(&m_criticalSection);
		break;
	case idPrimitive::Mutex:
		CloseHandle(&m_hMutex);
		break;
	case idPrimitive::Semaphore:
		CloseHandle(&m_hSemaphore);
		break;
	case idPrimitive::Event:
		CloseHandle(&m_pauseEvent);
		CloseHandle(&m_hEvent);
		break;
	default:
		break;
	}
}


CBankClient * CBank::CreateClient()
{
	unsigned int clientId = m_clients.size();
	m_clients.push_back(CBankClient(this, clientId));

	return &m_clients.back();
}

void CBank::UpdateClientBalance(size_t index, int value)
{
	if (!IsBetween(index, size_t(0), m_clients.size() - 1))
	{
		throw std::runtime_error("Index more amount clients");
	}
	UpdateClientBalance(m_clients[index], value);
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	if(EnableSynchronizationPrimitive(client))
	{

		int totalBalance = GetTotalBalance();
		std::cout << "Client " << client.GetId() << ". Total = " << totalBalance << "." << std::endl;


		//SomeLongOperations();
		totalBalance += value;

		std::cout
			<< " Value = " << value
			<< " and balance will " << totalBalance
			<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

		std::cout << "Check ! Client " << client.m_id << std::endl;
		// Balance not must be less zero
		if (totalBalance < 0)
		{
			std::cout << "==================================" << std::endl;
			std::cout << "! ERROR ! Client " << client.m_id << std::endl;
			std::cout << "Balance = " << GetTotalBalance() << std::endl;
			std::cout << "Value = " << value << std::endl;
			std::cout << "Set Value = " << totalBalance + value << std::endl;
			std::cout << "Balance not must be less zero!!!" << std::endl;
			DisableSynchronizationPrimitive();
			return;
		}


		Sleep(client.m_id);
		std::cout << "=== Removal of money === Client " << client.m_id << std::endl;
		UpdateTotalBalance(value);

		DisableSynchronizationPrimitive();
	}

}


int CBank::GetAffinityMask(size_t amountThread, size_t threadIndex)
{
	int mask = 0x0000;

	if (amountThread / m_amountCpu == 0)
	{
		return 1;
	}

	int cpuIndex = (threadIndex) / (amountThread / m_amountCpu);
	if ((amountThread % m_amountCpu == 1) && (cpuIndex > 0))
	{
		cpuIndex--;
	}
	return int(pow(2.f, cpuIndex));
}

bool CBank::EnableSynchronizationPrimitive(CBankClient &client)
{
	switch (m_idPrimitive)
	{
	case idPrimitive::CriticalSection:
		EnterCriticalSection(&m_criticalSection);
		return true;
		break;
	case idPrimitive::Mutex:
		WaitForSingleObject(m_hMutex, INFINITE);
		return true;
		break;
	case idPrimitive::Semaphore:
		WaitForSingleObject(m_hSemaphore, INFINITE);
		return true;
		break;
	case idPrimitive::Event:
		if (&m_clients[m_randomIndex] == &client)
		{
			SetEvent(m_hEvent);
			return true;
		}
		WaitForSingleObject(m_pauseEvent, INFINITE);
		return false;
		
		break;
	default:
		return false;
		break;
	}
}

void CBank::DisableSynchronizationPrimitive()
{
	switch (m_idPrimitive)
	{
	case idPrimitive::CriticalSection:
		LeaveCriticalSection(&m_criticalSection);
		break;
	case idPrimitive::Mutex:
		ReleaseMutex(m_hMutex);
		break;
	case idPrimitive::Semaphore:
		ReleaseSemaphore(m_hSemaphore, 1, NULL);
		break;
	case idPrimitive::Event:
		m_randomIndex = size_t(rand() % m_threads.size());

		ResetEvent(m_hEvent);

		SetEvent(m_pauseEvent);
		break;
	default:
		break;
	}

}

void CBank::CreateThreads(size_t amountCpu)
{
	m_amountCpu = amountCpu;
	for (size_t index = 0; index < m_clients.size(); ++index)
	{
		auto & client = m_clients[index];//ThreadFunction
		m_threads.push_back(CreateThread(NULL, 0, &client.ThreadErrorFunction, &client, CREATE_SUSPENDED, NULL));
		SetThreadAffinityMask(m_threads.back(), GetAffinityMask(m_clients.size(), index));
	}
}

void CBank::ResumeThreads()
{
	m_isUpdate = true;
	m_randomIndex = size_t(rand() % m_threads.size());
	for (auto & thread : m_threads)
	{
		ResumeThread(thread);
	}
	// ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::UpdateTotalBalance(int value)
{
	m_totalBalance += value;
}

void CBank::SomeLongOperations()
{
	Sleep(GetSleepDuration());
}

unsigned int CBank::GetSleepDuration()
{
	// -100 .. 100
	return rand() % 201 - 100;
}