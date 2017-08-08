#include <iostream>
#include <Windows.h>
#include<tchar.h>
using namespace std;
int main(int argc, char *argv[])
{
	/*DWORD dwExitCode;
	PROCESS_INFORMATION procInf;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));*/
	if (argc == 1)
	{
		cout << "                   PARAMETERS OF COMMAND LINE WERE NOT FOUND!"<<endl;
		system("pause");
		return 0;
	}
	else if (!(strcmp(argv[1], "MASTER")))
	{
		cout << "                     THE PROGRAM 'SLAVE' IS RUN FROM 'MASTER'" << endl;
		cout << "MASTER process ID : " << argv[3] << endl;
	}
	else if (!(strcmp(argv[1], "cmd")))
	{
		cout << "                     THE PROGRAM 'SLAVE' IS RUN INDEPENDENTLY" << endl;
		cout << "SLAVE process ID: " << GetCurrentProcessId()<<endl;

	}
	for(int i=0;i<4;i++)
	{
		cout<<argv[i]<<endl;
	 }
		cout << "The string of simbols: " << argv[2] << endl;
	system("pause");
	return 0;
}
