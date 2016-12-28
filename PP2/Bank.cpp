#include "stdafx.h"
#include "Bank.h"

static const unsigned SLEEP_TIME = 4u;

CBank::CBank(int clientsCount, const CPrimitivesHelper & primitivesHelper)
	: m_primitivesHelper(primitivesHelper)
	, m_totalBalance(0)
{
	for (int i = 0; i < clientsCount; i++)
	{
		CreateClient();
	}
}

std::shared_ptr<CBankClient> CBank::CreateClient()
{
	auto clientId = unsigned(m_clients.size());
	auto client = std::make_shared<CBankClient>(this, clientId);
	m_clients.emplace_back(client);
	m_threads.emplace_back(CreateClientsThreadWithPriority(client.get(), THREAD_BASE_PRIORITY_IDLE));

	return client;
}

void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	m_primitivesHelper.EnterPrimitiveZone();
	int totalBalance = GetTotalBalance();
	std::cout << "===StartUpdateClientBalance===" << std::endl;
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance + value > 0)
	{
		SetTotalBalance(m_totalBalance + value);
	}
	else
	{
		std::cout << "!ERROR!" << std::endl;
	}

	m_primitivesHelper.LeavePrimitiveZone();

	std::cout << "===FinishClientBalance===" << std::endl << std::endl;
}

int CBank::GetTotalBalance()const
{
	return m_totalBalance;
}

void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::WaitForThreadsComplited()
{
	WaitForMultipleObjects(DWORD(m_threads.size()), m_threads.data(), TRUE, INFINITE);
}

void CBank::SomeLongOperations()
{
	//TODO
	Sleep(SLEEP_TIME);
}

HANDLE CBank::CreateClientsThreadWithPriority(CBankClient * bankClient, int priority)
{
	auto thread = CreateThread(NULL, 0, &bankClient->ThreadFunction, bankClient, 0, NULL);
	SetThreadPriority(thread, priority);
	return thread;
}
