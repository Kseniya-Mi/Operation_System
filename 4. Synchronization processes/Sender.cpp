#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    string binaryFileName = argv[1];
    fstream file;
    int option;
    char message[20];

    HANDLE hStartEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"Process Started");
    if (hStartEvent == NULL)
    {
        return GetLastError();
    }

    HANDLE hInputReadySemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"Input Semaphore started");
    if (hInputReadySemaphore == NULL)
    {
        return GetLastError();
    }

    HANDLE hOutputReadySemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"Output Semaphore started");
    if (hOutputReadySemaphore == NULL)
    {
        return GetLastError();
    }

    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"mutex");

    SetEvent(hStartEvent);

    while (true) 
    {
	    
	cout << "Choose an action: \n";
	cout << "Press \"1\" to  write message \n";
	cout << "Press \"0\" to exit\n";
	cin >> option;
	    
	if(option == 0)
	{
		cout << "The process is finish ";
		break;
	}

        if(option == 1)
	{
            WaitForSingleObject(hMutex, INFINITE);
            file.open(binaryFileName, std::ios::out | std::ios::app | std::ios::trunc);

            string msg;
            cout << "Input message to add\n";
            cin >> msg;

            for (int i = 0; i < msg.length(); i++)
            {
                message[i] = msg[i];
            }
            for (int i = msg.length(); i < 20; i++)
            {
                message[i] = '\0';
            }
            
            message[19] = '\n';

            ReleaseMutex(hMutex);
            ReleaseSemaphore(hOutputReadySemaphore, 1, NULL);

            if (ReleaseSemaphore(hInputReadySemaphore, 1, NULL) != 1) 
            {
                cout << "file is full";

                ReleaseSemaphore(hOutputReadySemaphore, 1, NULL);
                WaitForSingleObject(hOutputReadySemaphore, INFINITE);
                ReleaseSemaphore(hOutputReadySemaphore, 1, NULL);
                ReleaseSemaphore(hInputReadySemaphore, 1, NULL);

               _getch();
            }
            else 
            {
		file.open(binaryFileName, std::ios::out | std::ios::app);
		    
                for (int i = 0; i < 20; i++)
                {
                    file << message[i];
                }
		    
		file.close();
            }		
	}
        
        if (option != 0 && option != 1)
		{
			cout << "Incorrect input\n Try again...";
			cin >> option;
		}
	}

    return 0;
}
