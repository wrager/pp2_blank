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
	unsigned int GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);
	static DWORD WINAPI ThreadErrorFunction(LPVOID lpParam);// Special function for testing

	friend CBank;

//////////////////////////////////////////////////////////////////////
// Data
private:
	unsigned	m_id;
	CBank *		m_bank;
};