#include "Bank.h"
#include "SyncPrimitives.h"

CBank::CBank(TypeSyncPrimitives type)
{
	m_syncPrimitives = new SyncPrimitives();
	m_syncPrimitives->type = type;
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}

CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}


CBankClient* CBank::CreateClient()
{
	unsigned clientId = static_cast<unsigned>(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId, m_syncPrimitives);
	m_clients.push_back(*client);
	return client;
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations(client);

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << totalBalance + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance + value > 0)
	{
		SetTotalBalance(totalBalance + value);
		std::cout << "Total Balance = " << GetTotalBalance() << std::endl;
	}
	if (totalBalance != GetTotalBalance() - value) {
		std::cout << "! ERROR !" << std::endl;
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
	Sleep((1000 + std::rand() % 3000) * (client.m_id + 1));
}