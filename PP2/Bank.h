#pragma once
#include <iostream>
#include <vector>
#include "BankClient.h"
#include "PrimitivesHelper.h"

class CBank
{
public:
	CBank(int clientsCount, const CPrimitivesHelper & primitivesHelper);
	void UpdateClientBalance(CBankClient& client, int value);
	void WaitForThreadsComplited();

private:
	std::shared_ptr<CBankClient> CreateClient();
	int GetTotalBalance()const;
	void SetTotalBalance(int value);
	void SomeLongOperations();
	static HANDLE CreateClientsThreadWithPriority(CBankClient * bankClient, int priority);

private:
	std::vector<HANDLE>	m_threads;
	int m_totalBalance;
	CPrimitivesHelper m_primitivesHelper;
	std::vector<std::shared_ptr<CBankClient>> m_clients;
};