#include "stdafx.h"
#include "BankClient.h"
#include "Bank.h"


CBankClient::CBankClient(CBank *bank, unsigned int id, Primitives *primitives) : m_bank(bank), m_id(id), m_handle(CreateThread(NULL, 0, ThreadFunction, this, 0, NULL)), m_syncPrimitives(primitives)
{
}


unsigned CBankClient::GetId()
{
	return m_id;
}

void CBankClient::ChoiceSyncMethod(PRIMITIVE_TYPE type, CBankClient *client)
{
	switch (type)
	{
	case PRIMITIVE_TYPE::CRITICAL_SECTION:
		EnterCriticalSection(&client->m_syncPrimitives->critical_section);
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
		LeaveCriticalSection(&client->m_syncPrimitives->critical_section);
		break;
	case PRIMITIVE_TYPE::SEMAPHORE:
		WaitForSingleObject(client->m_syncPrimitives->hSemaphore, INFINITE);
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
		ReleaseSemaphore(client->m_syncPrimitives->hSemaphore, 1, NULL);
		break;
	case PRIMITIVE_TYPE::MUTEX:
		WaitForSingleObject(client->m_syncPrimitives->hMutex, INFINITE);
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
		ReleaseMutex(client->m_syncPrimitives->hMutex);
		break;
	case PRIMITIVE_TYPE::EVENT:
		WaitForSingleObject(client->m_syncPrimitives->hEvent, INFINITE);
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
		SetEvent(client->m_syncPrimitives->hEvent);
		break;
	case PRIMITIVE_TYPE::NO:
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
		break;
	default:
		break;
	}
}


DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;

	srand(client->m_id);

	while (true)
	{
		Sleep(GetSleepDuration(client));
		ChoiceSyncMethod(client->m_syncPrimitives->type, client);
	}
	return 0;
}


unsigned int CBankClient::GetSleepDuration(CBankClient *client)
{
	return (1000 + rand() % 2999) * (client->m_id + 1);
}


unsigned int CBankClient::GetBalanceChangeValue()
{
	return (-100 + rand() % 201);
}