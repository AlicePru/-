#include<iostream>
#include<windows.h>
#include<tchar.h>
using namespace std;
//struct DllFile
//{
//	WCHAR FileName[MAX_PATH];
//	SYSTEMTIME CreationTime;
//};

int main()
{
	HANDLE hFile;
	CreateDirectory("c:\\FIND ", NULL);
	hFile = CreateFile(_TEXT("c:\\FIND\\find.dat"), GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WIN32_FIND_DATA lpFile;
	DWORD n;
	SYSTEMTIME sysTime;
	int c = 0;
	SetCurrentDirectory(_TEXT("c:\\Windows\\System32"));

	HANDLE	hFindFile = FindFirstFile(_TEXT("*.dll"), &lpFile);
	FileTimeToSystemTime(&lpFile.ftCreationTime, &sysTime);

	//DllFile file;
	//wcscpy(file.FileName, lpFile.cFileName);
	//hFindFile.CreationTime = sysTime;
	WriteFile(hFile, &h, sizeof(DllFile), &n, NULL);

	for (int i = 1; i < 15; i++)
	{
		if (FindNextFile(hFindFile, &lpFile) != ERROR_NO_MORE_FILES)
		{
			ZeroMemory(&file, sizeof(DllFile));
			FileTimeToSystemTime(&lpFile.ftLastWriteTime, &sysTime);
			wcscpy(file.FileName, lpFile.cFileName);
			file.CreationTime = sysTime;
			WriteFile(hFile, &file, sizeof(DllFile), &n, NULL);
		}
		else
		{
			cout << "No such files";
			break;
		}
	}
	CloseHandle(hFile);
	hFile = CreateFile(_TEXT("c:\\FIND\\find.dat"), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DllFile ff;
	for (int i = 0; i < 15; i++)
	{
		ReadFile(hFile, &ff, sizeof(DllFile), &n, NULL);
		_tprintf(_T("Contain of find.dat: %s \t\t"), ff.FileName);
		_tprintf(_T("time: %d  "), ff.CreationTime.wHour);
		_tprintf(_T("%d \n"), ff.CreationTime.wMinute);
	}
	CloseHandle(hFile);
	system("pause");
	return 0;
}
