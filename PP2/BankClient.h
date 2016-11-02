#pragma once
#include <Windows.h>

class CBank;

class CBankClient
{
public:
	CBankClient(CBank *bank, unsigned id);
	unsigned GetId();

private:
	static unsigned GetSleepDuration(CBankClient *client);
	static unsigned GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	friend CBank;

	CBank *m_bank;
	unsigned m_id;
};