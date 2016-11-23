#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (string(argv[1]) == "?")
		{
			std::cout << "pp2.exe <bankClientsNumber> <syncPrimitive>\n\tmutex\n\tsemaphore\n\tevent\n\tcritical_section\nif syncPrimitive don`t specified or incorrect, primitive won`t use";
		}
		else
		{
			int clientsCount = atoi(argv[1]);

			if (clientsCount > 0)
			{

				PrimitivesCollection collection(argc > 2 ? argv[2] : "");
				shared_ptr<CBank> bank = make_shared<CBank>(clientsCount, collection);

				//fixed TODO
				bank->WaitForThreadsComplited();
			}
		}

		return 0;
	}

	std::cout << "Error.\nUsage:pp2.exe <bankClientsNumber>\npp2.exe -? for help";
    return 1;
}