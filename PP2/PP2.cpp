#include "stdafx.h"
#include <iostream>
#include "CBank.h"
#include "CBankClient.h"

int main()
{
	CBank* bank = new CBank();
	CBankClient* client1 = bank->CreateClient();
	CBankClient* client2 = bank->CreateClient();

	// TODO: WaitForMultipleObjects
	while (true)
	{
	}

    return 0;
}