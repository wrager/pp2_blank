#include "CBank.h"
#include "stdafx.h"

CBank::CBank(idPrimitive idPrimitiveType)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;


	m_idPrimitive = idPrimitiveType;
	switch (m_idPrimitive)
	{
	case idPrimitive::CriticalSection:
		InitializeCriticalSection(&m_criticalSection);
		break;
	case idPrimitive::Mutex:
		m_hMutex = CreateMutex(NULL, false, NULL);
		break;
	case idPrimitive::Semaphore:
		m_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		break;
	case idPrimitive::Event:
		m_hEvent = CreateEvent(NULL, true , false, NULL);
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

	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << ". Total = " << totalBalance << "." << std::endl;

	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< " Value = " << value
		<< " and balance will " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Balance not must be less zero
	if (totalBalance < 0)
	{
		std::cout << "! ERROR !" << std::endl;
		std::cout << "totalBalance < GetTotalBalance() " << std::endl;// TODO : fix message
		return;
	}

	EnableSynchronizationPrimitive();

	std::cout << "=== Removal of money ==="<< std::endl;
	SetTotalBalance(totalBalance);

	DisableSynchronizationPrimitive();
}


int CBank::GetAffinityMask(size_t amountThread, size_t threadIndex)
{
	int mask = 0x0000;

	const size_t amountCpu = 2;// TODO : transfer to other place
	if (amountThread / amountCpu == 0)
	{
		return 1;
	}

	int cpuIndex = (threadIndex) / (amountThread / amountCpu);
	if ((amountThread % amountCpu == 1) && (cpuIndex > 0))
	{
		cpuIndex--;
	}
	return int(pow(2.f, cpuIndex));
}

void CBank::EnableSynchronizationPrimitive()
{
	switch (m_idPrimitive)
	{
	case idPrimitive::CriticalSection:
		EnterCriticalSection(&m_criticalSection);
		break;
	case idPrimitive::Mutex:
		WaitForSingleObject(m_hMutex, INFINITE);
		break;
	case idPrimitive::Semaphore:
		WaitForSingleObject(m_hSemaphore, INFINITE);
		break;
	case idPrimitive::Event:
		SetEvent(m_hEvent);
		break;
	default:
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
		ResetEvent(m_hEvent);
		break;
	default:
		break;
	}

}

void CBank::CreateThreads(size_t amountCpu)
{
	for (auto & client : m_clients)
	{
		m_threads.push_back(CreateThread(NULL, 0, &client.ThreadFunction, &client, CREATE_SUSPENDED, NULL));
		SetThreadAffinityMask(m_threads.back(), GetAffinityMask(m_threads.size(), amountCpu));
	}


}

void CBank::ResumeThreads()
{
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


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
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