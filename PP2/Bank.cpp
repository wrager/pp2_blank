#include "stdafx.h"
#include "Bank.h"




CBank::CBank(TypeSyncPrimitives type)
{
	m_syncPrimitives = new SyncPrimitives();
	m_syncPrimitives->type = type;
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}

CBank::~CBank()
{
	CloseHandle(m_syncPrimitives->hMutex);
	CloseHandle(m_syncPrimitives->hSemaphore);
	CloseHandle(m_syncPrimitives->hEvent);
	DeleteCriticalSection(&m_syncPrimitives->critical_section);
	m_clients.clear();
	delete m_syncPrimitives;
}

CBankClient* CBank::CreateClient()
{
	
	unsigned int clientId = static_cast<unsigned>(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId, m_syncPrimitives);
	m_clients.push_back(*client);
	return client;
}



void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations(client);
	totalBalance += value;
	
	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << (totalBalance) << "." << std::endl;

	if (totalBalance != GetTotalBalance() + value)
	{
		std::cout << "Error!!!!!!!!" << std::endl;
	}
	else if (totalBalance > 0)
	{
		SetTotalBalance(totalBalance);
		std::cout << "Total Balance = " << GetTotalBalance() << std::endl;	
	}
	else
	{
		std::cout << "There is no possibility to withdraw money" << std::endl;
	}
}



size_t CBank::GetClientsCount() const
{
	return m_clients.size();
}

HANDLE * CBank::GetClientsHandles() const
{
	std::vector<HANDLE> handles;

	for (auto const& client : m_clients)
	{
		handles.push_back(client.m_handle);
	}

	return handles.data();
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations(CBankClient const &client)
{
	Sleep((1000 + rand() % 3000) * (client.m_id+ 1));
}