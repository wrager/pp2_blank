#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

using namespace std;

int main()
{
	shared_ptr<CBank> bank = make_shared<CBank>();
	shared_ptr<CBankClient> client1 = bank->CreateClient();
	shared_ptr<CBankClient> client2 = bank->CreateClient();
	shared_ptr<CBankClient> client3 = bank->CreateClient();
	shared_ptr<CBankClient> client4 = bank->CreateClient();
	shared_ptr<CBankClient> client5 = bank->CreateClient();
	shared_ptr<CBankClient> client6 = bank->CreateClient();
	// TODO: WaitForMultipleObjects
	bank->WaitForThreadsComplited();

    return 0;
}