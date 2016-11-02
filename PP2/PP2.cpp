#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

using namespace std;

int main()
{
	shared_ptr<CBank> bank = make_shared<CBank>();
	shared_ptr<CBankClient> client1 = bank->CreateClient();
	shared_ptr<CBankClient> client2 = bank->CreateClient();

	// TODO: WaitForMultipleObjects
	while (true)
	{
	}

    return 0;
}