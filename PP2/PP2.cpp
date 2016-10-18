#include "stdafx.h"
#include <iostream>
#include "CBank.h"
#include "CBankClient.h"

using namespace std;

int main()
{
	shared_ptr<CBank> bank = make_shared<CBank>();
	CBankClient* client1 = bank->CreateClient();
	CBankClient* client2 = bank->CreateClient();

	// TODO: WaitForMultipleObjects
	while (true)
	{
	}

    return 0;
}