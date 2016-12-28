#pragma once
#include <Windows.h>

class CBank;

class CBankClient
{
public:
	unsigned GetId();
	CBankClient(CBank *bank, unsigned id);

private:
	static unsigned GetSleepDuration(CBankClient *client);
	static unsigned GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	friend CBank;

	CBank *m_bank;
	unsigned m_id;
};