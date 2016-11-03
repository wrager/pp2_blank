#include "CBankClient.h"


CBankClient::CBankClient(CBank *bank, unsigned int id)
{
	m_bank = bank;
	m_id = id;
}


unsigned int CBankClient::GetId()
{
	return m_id;
}


DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;
	srand(client->m_id);
	while (true)
	{
		Sleep(GetSleepDuration(client));
		client->m_bank->UpdateClientBalance(*client, client->GetBalanceChangeValue());
	}
	return 0;
}

DWORD CBankClient::ThreadErrorFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;
	while (true)
	{
		client->m_bank->UpdateClientBalance(*client, -90);
	}
	return 0;
}


unsigned int CBankClient::GetSleepDuration(CBankClient *client)
{
	return (1000 + rand() % 3000) * (client->m_id + 1);
}


unsigned int CBankClient::GetBalanceChangeValue()
{
	// -100 .. 100
	//% 201 - 100;
	return -rand() % (m_bank->GetTotalBalance() + 1 + 50) + 50;
}