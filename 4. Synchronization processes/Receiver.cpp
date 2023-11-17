#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	fstream file;
	string binaryFileName;
	string message;
	int amountOfNotes;
	int amountOfSenders;
	int option;
	HANDLE* hEventStarted;
	string SenderEXE;
	wstring convertingToLPWSTR;
	LPWSTR SenderLPWSTR;

	cout << "Enter binary file name: \n";
	cin >> binaryFileName;
	cout << "Enter amount of notes: \n";
	cin >> amountOfNotes;

	file.open(binaryFileName, std::ios::out | std::ios::trunc);
	file.close();

	cout << "Enter amount of senders processes: \n";
	cin >> amountOfSenders;

	HANDLE hMutex = CreateMutex(NULL, 0, L"mutex");

	HANDLE hInputReadySemaphore = CreateSemaphore(NULL, 0, amountOfNotes, L"Input Semaphore started");
	if (hInputReadySemaphore == NULL)
	{
		return GetLastError();
	}

	HANDLE hOutputReadySemaphore = CreateSemaphore(NULL, 0, amountOfSenders, L"Output Semaphore started");
	if (hOutputReadySemaphore == NULL)
	{
		return GetLastError();
	}

	hEventStarted = new HANDLE[amountOfSenders];

	for (int i = 0; i < amountOfSenders; i++)
	{
		SenderEXE = "Sender.exe " + binaryFileName;
		convertingToLPWSTR = wstring(SenderEXE.begin(), SenderEXE.end());
		SenderLPWSTR = &convertingToLPWSTR[0];

		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (!CreateProcess(NULL, SenderLPWSTR, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			std::cout << "The Sender Process is not started.\n";
			return GetLastError();
		}

		hEventStarted[i] = CreateEvent(NULL, FALSE, FALSE, L"Process Started");

		if (hEventStarted[i] == NULL)
		{
			return GetLastError();
		}

		CloseHandle(pi.hProcess);
	}

	WaitForMultipleObjects(amountOfSenders, hEventStarted, TRUE, INFINITE);
	ReleaseMutex(hMutex);
	
	file.open(binaryFileName, std::ios::in);

	while (true)
	{
		cout << "\nChoose an action: \n";
		cout << "Press \"1\" to  read message \n";
		cout << "Press \"0\" to exit\n";
		cin >> option;
		
		if (option == 0)
		{
			cout << "The process is finish ";
			break;
		}
		else if (option == 1)
		{
			WaitForSingleObject(hInputReadySemaphore, INFINITE);
			WaitForSingleObject(hMutex, INFINITE);

			getline(file, message);
			cout << message;

			ReleaseSemaphore(hOutputReadySemaphore, 1, NULL);
			ReleaseMutex(hMutex);
		}

	        if (option != 0 && option != 1)
	        {
			cout << "Incorrect input\n Try again...";
			cin >> option;
	        }
        }
	
	for (int i = 0; i < amountOfSenders; i++)
	{
		CloseHandle(hEventStarted[i]);
	}

        CloseHandle(hInputReadySemaphore);
	CloseHandle(hOutputReadySemaphore);

	return 0;
}
