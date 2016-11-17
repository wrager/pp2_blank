#pragma once
#include <Windows.h>
#include "SyncPrimitives.h"

class CBank;

class CBankClient
{
public:
	unsigned GetId();
	~CBankClient() = default;

private:
	CBankClient(CBank *bank, unsigned id, SyncPrimitives *typeSync);
	static unsigned GetSleepDuration(CBankClient *client);
	static unsigned GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

private:
	friend CBank;
	HANDLE m_handle;
	CBank *m_bank;
	unsigned m_id;
	SyncPrimitives *m_syncPrimitives = nullptr;
};