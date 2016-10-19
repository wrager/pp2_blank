#pragma once
#include <Windows.h>
#include "CBank.h"
class CBank;

class CBankClient
{
public:
//////////////////////////////////////////////////////////////////////
// Methods
public:
	unsigned int GetId();
private:

	CBankClient(CBank *bank, unsigned int id);
	static unsigned int GetSleepDuration(CBankClient *client);
	static unsigned int GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	friend CBank;

//////////////////////////////////////////////////////////////////////
// Data
private:
	unsigned	m_id;
	CBank *		m_bank;
};