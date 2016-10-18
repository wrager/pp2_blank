#include "CBankClient.h"


CBankClient::CBankClient(CBank *bank, unsigned int id)
{
	m_bank = bank;
	m_id = id;

	CreateThread(NULL, 0, ThreadFunction, this, 0, NULL);
}


unsigned int CBankClient::GetId()
{
	return m_id;
}


DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;
	// TODO: srand(client->m_id);
	while (true)
	{
		Sleep(GetSleepDuration(client));
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
	}
	return 0;
}


unsigned int CBankClient::GetSleepDuration(CBankClient *client)
{
	// FIXTODO: check correctness of running application with no sleep, even in CBank

	// Was
	//		return (1000 + rand() % 3000) * (client->m_id + 1);
	// Stand
	//		if "* (client->m_id + 1)" had there then first client
	//		constantly would update, time sleep = 0

	// 1000 .. 3999
	return (1000 + rand() % 3000);

}


unsigned int CBankClient::GetBalanceChangeValue()
{
	// -100 .. 100
	return rand() % 201 - 100;
}