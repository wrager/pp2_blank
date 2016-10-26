#include "CBank.h"
#include "stdafx.h"

CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}


CBankClient * CBank::CreateClient()
{
	unsigned int clientId = m_clients.size();
	m_clients.push_back(CBankClient(this, clientId));

	return &m_clients.back();
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;

	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Balance not must be less zero
	if (totalBalance < 0)
	{
		std::cout << "! ERROR !" << std::endl;
		std::cout << "totalBalance < GetTotalBalance() " << std::endl;// TODO : fix message
	}

	SetTotalBalance(totalBalance);
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