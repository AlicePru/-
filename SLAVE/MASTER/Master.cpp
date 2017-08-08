#include <windows.h>
#include <time.h>
#include <iostream>
#include <tchar.h>
using namespace std;

int main(int argc, char ** argv)
{
	srand(time(0));
	char str[10];
	char cmd[255];
	PROCESS_INFORMATION procInf;
	STARTUPINFOA si;
	DWORD currPID, dwExitCode;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	if (argc == 1)
	{
		for (int i = 0; i< 10; i++)
		{
			str[i] = rand() % 65+65 ;
			//cout << str[i];
		}
		currPID = GetCurrentProcessId();
	sprintf_s(cmd,"SLAVE.exe MASTER %s %d", str, currPID);
	if (CreateProcessA(NULL,cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &procInf) == TRUE)
	{
		cout << "MASTER process ID: " << currPID<<endl;
		for (int i = 0; i< 10; i++)
		{
			cout << str[i];
		}
		WaitForSingleObject(procInf.hProcess, INFINITE);
	}
	else
	{
		cout << "Error" << endl;
	}
}
	
	CloseHandle(procInf.hProcess);
	system("pause");
	return 0;
}