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