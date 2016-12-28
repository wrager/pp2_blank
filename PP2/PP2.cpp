#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <memory>
#include "SynchronizationPrimitivesType.h"

static const std::string HELP_FLAG = "/?";

void PrintHelp()
{
	std::cout << "***Help:" << std::endl
		 << "PP2.exe <Amount Clients> <Synchronization Primitive Type>" << std::endl
		 << "PP2.exe /? - to print help" << std::endl
		 << "Synhronization Primitive Type:" << std::endl
		<< "	1 - CriticalSection" << std::endl
		<< "	2 - Mutex" << std::endl
		<< "	3 - Semaphore" << std::endl
		<< "	4 - Event" << std::endl;
	std::cout << "***" << std::endl;
}

bool CorrectArgumentsCount(int argc)
{
	return argc == 2 || argc == 3;
}

int main(int argc, char * argv[])
{
	if (!CorrectArgumentsCount(argc))
	{
		std::cout << "Incorrect arguments count. Usage /? flag to get help." << std::endl;
		return EXIT_FAILURE;
	}

	if (argv[1] == HELP_FLAG)
	{
		PrintHelp();
		return EXIT_FAILURE;
	}

	int clientsCount = atoi(argv[1]);

	if (clientsCount > 0)
	{
		auto primitiveType = SynchranizationPrimitivesType::None;
		try
		{
			PRIMITIVES_MAP.at(argc > 2 ? argv[2] : "None");
		}
		catch (...)
		{
			std::cout << "Incorrect primitive type:" << argv[2] << std::endl;
		}

		CPrimitivesHelper primitivesHelper(primitiveType);
		CBank bank(clientsCount, primitivesHelper);

		//fixed TODO
		bank.WaitForThreadsComplited();
	}
	else
	{
		std::cout << "Clients count must be > 0" << std::endl;
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}