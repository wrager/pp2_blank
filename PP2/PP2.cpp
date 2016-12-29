#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <iostream>
#include <string>
#include <map>

void ShowHelp()
{
	std::cout << std::endl << "To start using the key in brackets." << std::endl << std::endl;
}

bool GetPrimitiveType(std::string const & stringType, PRIMITIVE_TYPE & type)
{
	if (stringType == "CS")
	{
		type = PRIMITIVE_TYPE::CRITICAL_SECTION;
		return true;
	}
	else if (stringType == "M")
	{
		type = PRIMITIVE_TYPE::MUTEX;
		return true;
	}
	else if (stringType == "E")
	{
		type = PRIMITIVE_TYPE::EVENT;
		return true;
	}
	else if (stringType == "S")
	{
		type = PRIMITIVE_TYPE::SEMAPHORE;
		return true;
	}
	else if (stringType == "NO")
	{
		type = PRIMITIVE_TYPE::NO;
		return true;
	}
	return false;
}

PRIMITIVE_TYPE GetTypeSyncPrimitivesInConsole()
{
	std::string val;
	bool isCorrectKey = false;
	PRIMITIVE_TYPE type;
	while (!isCorrectKey)
	{
		std::cout << "Please enter whether you want to use synchronization primitives or not"
			<< " (critical section(CS), mutex(M), semaphore(S), event(E) or NO ) : ";

		std::getline(std::cin, val);
		isCorrectKey = GetPrimitiveType(val, type);

		if (val == "/?")
		{
			ShowHelp();
		}
		else if (!isCorrectKey)
		{
			std::cout << "Incorrect key. Try again" << std::endl;
		}
	}
	return type;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error! Usage: program.exe clientNumber " << std::endl;
		return EXIT_FAILURE;
	}
	PRIMITIVE_TYPE key;
	key = GetTypeSyncPrimitivesInConsole();
	size_t clientNumber = atoi(argv[1]);

	std::unique_ptr<CBank> bank = std::make_unique<CBank>(key);

	std::vector<CBankClient*> clients;

	for (size_t i = 0; i != clientNumber; ++i)
	{
		clients.push_back(bank->CreateClient());
	}
	while (true)
	{
		WaitForMultipleObjects(static_cast<DWORD>(bank->GetClientsCount()), bank->GetClientsHandles(), TRUE, INFINITE);
	}
	return 0;
}