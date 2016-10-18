#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "CBankClient.h"

class CBankClient;

class CBank
{
public:
	CBank();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	CBankClient *					CreateClient();
	void							UpdateClientBalance(CBankClient& client, int value);
private:
	int								GetTotalBalance();
	void							SetTotalBalance(int value);
	void							SomeLongOperations();
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<CBankClient>		m_clients;
	int								m_totalBalance;

	
};