#pragma once
#include <iostream>
#include <vector>

#include "BankClient.h"
#include "SyncPrimitives.h"

class CBank
{
public:
	CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	size_t GetClientsCount() const;
	HANDLE* GetClientsHandles() const;
private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;
	SyncPrimitives *m_syncPrimitives = nullptr;
	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};