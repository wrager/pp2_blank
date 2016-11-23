#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "BankClient.h"
#include "SynchronizationPrimitives.h"

class CBank
{
public:
	CBank(PrimitivesCollection & collection);
	std::shared_ptr<CBankClient> CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	DWORD WaitForThreadsComplited();

private:
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE>	m_threads;
	int m_totalBalance;
	PrimitivesCollection& m_primitives;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
};