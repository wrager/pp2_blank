#include "stdafx.h"
#include "Bank.h"

const float SLEEP_TIME = 4.f;
using namespace std;

CBank::CBank(int clientsCount, PrimitivesCollection & collection)
	: m_clients()
	, m_totalBalance(0)
	, m_threads()
	, m_primitives(collection)
{
	for (int i = 0; i < clientsCount; i++)
	{
		CreateClient();
	}
}


shared_ptr<CBankClient> CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	shared_ptr<CBankClient> client = make_shared<CBankClient>(this, clientId);
	m_clients.push_back(*client);
	m_threads.emplace_back(CreateThread(NULL, 0, &client->ThreadFunction, &*client, 0, NULL));
	SetThreadPriority(m_threads.back(), THREAD_BASE_PRIORITY_IDLE);

	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	m_primitives.EnterPrimitiveZone();
	int totalBalance = m_totalBalance;
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << m_totalBalance << "." << std::endl;
	SomeLongOperations();
	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance + value
		<< ". Must be: " << m_totalBalance + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance + value > 0)
	{
		SetTotalBalance(m_totalBalance + value);
	}
	else
	{
		std::cout << "!ERROR!" << std::endl;
	}
	m_primitives.LeavePrimitiveZone();
}

DWORD CBank::WaitForThreadsComplited()
{
	return WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
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
	//fixed TODO
	Sleep(SLEEP_TIME);
}