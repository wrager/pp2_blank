#pragma once
#include <iostream>
#include <vector>
#include "BankClient.h"

class CBank
{
public:
	CBank(PRIMITIVE_TYPE type);
	~CBank();

	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);

	HANDLE* GetClientsHandles() const;
	size_t GetClientsCount() const;

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;
	std::shared_ptr<Primitives> m_syncPrimitives;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations(CBankClient const &client);
};
