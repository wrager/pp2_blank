#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "BankClient.h"

class CBank
{
public:
	CBank();
	std::shared_ptr<CBankClient> CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	DWORD WaitForThreadsComplited();

private:
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE>	m_threads;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};