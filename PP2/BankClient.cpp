#include "stdafx.h"
#include "BankClient.h"
#include "Bank.h"


CBankClient::CBankClient(CBank *bank, unsigned id)
	: m_bank(bank)
	, m_id(id)
{
}

unsigned CBankClient::GetId()
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
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
	}
	return 0;
}

unsigned CBankClient::GetSleepDuration(CBankClient *client)
{
	// TODO: check correctness of running application with no sleep, even in CBank

	// 1000 .. 3999
	return (1000 + rand() % 3000) * (client->m_id + 1);
}

unsigned CBankClient::GetBalanceChangeValue()
{
	// -100 .. 100
	return rand() % 201 - 100;
}