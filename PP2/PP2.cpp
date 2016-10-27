#include "stdafx.h"
#include <iostream>
#include "CBank.h"
#include "CBankClient.h"
#include "main.h"

using namespace std;


void CheckParametrs(int argc)
{
	if ( (argc != AMOUNT_ARGUMENTS) && (argc != AMOUNT_ARGUMENTS_WITH_ADDITIONAL) )
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS 
								+ to_string(AMOUNT_ARGUMENTS)
								+ " or "
								+ to_string(AMOUNT_ARGUMENTS_WITH_ADDITIONAL)
								+ "\n If use additional parametr");
	}
}

void PrintHelp()
{
	std::cout << "Help" << std::endl;
	std::cout << "First parametr - amount clients" << std::endl;
	std::cout << "Second parametr - type primitive synchronization" << std::endl;
	std::cout << std::endl;
	std::cout << "Value parametr:" << std::endl;
	std::cout << "1 - critical section" << std::endl;
	std::cout << "2 - mutex" << std::endl;
	std::cout << "3 - semaphore" << std::endl;
	std::cout << "4 - event" << std::endl;
	std::cout << std::endl;
	std::cout << "Third parametr(additional) - call help" << std::endl;
}

bool CheckAdditionalParametr(int argc, char * argv[])
{
	if ( (argc == AMOUNT_ARGUMENTS_WITH_ADDITIONAL) )
	{
		if (argv[3] == "?")
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

idPrimitive CheckRuntimeParametr(int argc, char * argv[])
{
	int value = atoi(argv[2]);

	switch (value)
	{
	case 1:
		return idPrimitive::CriticalSection;
		break;
	case 2:
		return idPrimitive::Mutex;
		break;
	case 3:
		return idPrimitive::Semaphore;
		break;
	case 4:
		return idPrimitive::Event;
		break;
	default:
		throw invalid_argument(MESSAGE_INCORRECT_RUNTIME_ARGUMENTS);
		break;
	}

}

int main(int argc, char * argv[])
{
	try
	{
		CheckParametrs(argc);

		if (CheckAdditionalParametr(argc, argv))
		{
			PrintHelp();
		}

		idPrimitive runtime = CheckRuntimeParametr(argc, argv);

		shared_ptr<CBank> bank = make_shared<CBank>(runtime);

		size_t amountClients = size_t(atoi(argv[1]));

		for (size_t index = 0; index < amountClients; ++index)
		{
			bank->CreateClient();
		}
		bank->CreateThreads(2);
		bank->ResumeThreads();

	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	

    return 0;
}