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
	std::cout << "Second parametr(additional) - call help" << std::endl;
}

int CheckAdditionalParametr(int argc, char * argv[])
{
	if ( (argc == AMOUNT_ARGUMENTS_WITH_ADDITIONAL) )
	{
		if (argv[2] == "?")
		{
			return true;
		}
	}
	else
	{
		return false;
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

		shared_ptr<CBank> bank = make_shared<CBank>();

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