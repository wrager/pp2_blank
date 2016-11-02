#include "stdafx.h"
#include "Bank.h"

const float SLEEP_TIME = 4.f;
using namespace std;

CBank::CBank()
	: m_clients()
	, m_totalBalance(0)
	, m_threads()
{
}


shared_ptr<CBankClient> CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	shared_ptr<CBankClient> client = make_shared<CBankClient>(this, clientId);
	m_clients.push_back(*client);
	m_threads.emplace_back(CreateThread(NULL, 0, &client->ThreadFunction, &*client, 0, NULL));
	return client;
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

	// Check correctness of transaction through actual total balance
	if (totalBalance < 0)
	{
		std::cout << "! ERROR !" << std::endl;
	}
	else
	{ 
		SetTotalBalance(totalBalance);
	}
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