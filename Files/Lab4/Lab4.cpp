#include<iostream>
#include<windows.h>
#include<tchar.h>

using namespace std;

int main()
{
	HANDLE hFile;
	CreateDirectory(_TEXT("c:\\FIND "), NULL);
	hFile = CreateFile(_TEXT("c:\\FIND\\find.dat"), GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//WIN32_FIND_DATA lpFile;
	WIN32_FIND_DATA lpFindFile;
	DWORD n;
	SYSTEMTIME sysTime,locTime;
	FILETIME lpCreationTime, lpLastAccessTime, lpLastWriteTime;
	SetCurrentDirectory(_TEXT("c:\\Windows\\System32"));
	ZeroMemory(&lpFindFile, sizeof(WIN32_FIND_DATA));
	HANDLE	hFindFile = FindFirstFile(_TEXT("*.dll"), &lpFindFile);
	FileTimeToSystemTime(&lpFindFile.ftCreationTime, &sysTime);
	SystemTimeToTzSpecificLocalTime(NULL, &sysTime, &locTime);
	WriteFile(hFile, &lpFindFile, sizeof(WIN32_FIND_DATA), &n, NULL);
	WriteFile(hFile, &locTime, sizeof(SYSTEMTIME), &n, NULL);

	for (int i = 1; i < 15; i++)
	{
		if (FindNextFile(hFindFile, &lpFindFile) != ERROR_NO_MORE_FILES)
		{
			FileTimeToSystemTime(&lpFindFile.ftCreationTime, &sysTime);
			SystemTimeToTzSpecificLocalTime(NULL, &sysTime, &locTime);
			WriteFile(hFile, &lpFindFile, sizeof(WIN32_FIND_DATA), &n, NULL);
			WriteFile(hFile, &locTime, sizeof(SYSTEMTIME), &n, NULL);


		}
		else
		{
			cout << "No such files";
			break;
		}
	}
	CloseHandle(hFile);
	hFile = CreateFile(_TEXT("c:\\FIND\\find.dat"), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WIN32_FIND_DATA files;
	SYSTEMTIME crTime;
	cout << "Contain of find.dat:" << endl;
	cout << " ";
	for (int i = 0; i < 15; i++)
	{
		ReadFile(hFile, &files, sizeof(WIN32_FIND_DATA), &n, NULL);
		_tprintf(_T("%s \t\t"), files.cFileName);
		ReadFile(hFile, &crTime, sizeof(SYSTEMTIME), &n, NULL);
		_tprintf(_T("Creation time: %d : %d\n"), crTime.wHour, crTime.wMinute);
	}

	CloseHandle(hFile);
	system("pause");
	return 0;
}

//#include<iostream>
//#include<windows.h>
//#include<tchar.h>
//using namespace std;
//struct DllFile
//{
//	char FileName[MAX_PATH];
//	SYSTEMTIME CreationTime;
//};
//
//int main()
//{
//	HANDLE hFile;
//	CreateDirectory("c:\\FIND ", NULL);
//	hFile = CreateFile(_TEXT("c:\\FIND\\find.dat"), GENERIC_WRITE, 0, NULL,
//		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	WIN32_FIND_DATA lpFile;
//	DWORD n;
//	SYSTEMTIME sysTime;
//	int c = 0;
//	SetCurrentDirectory(_TEXT("c:\\Windows\\System32"));
//
//	HANDLE	hFindFile = FindFirstFile(_TEXT("*.dll"), &lpFile);
//	FileTimeToSystemTime(&lpFile.ftCreationTime, &sysTime);
//
//	DllFile file;
//	_tcscpy_s(file.FileName, lpFile.cFileName);
//	file.CreationTime = sysTime;
//	WriteFile(hFile, &file, sizeof(DllFile), &n, NULL);
//
//	for (int i = 1; i < 15; i++)
//	{
//		if (FindNextFile(hFindFile, &lpFile) != ERROR_NO_MORE_FILES)
//		{
//			ZeroMemory(&file, sizeof(DllFile));
//			FileTimeToSystemTime(&lpFile.ftLastWriteTime, &sysTime);
//			_tcscpy_s(file.FileName, lpFile.cFileName);
//			file.CreationTime = sysTime;
//			WriteFile(hFile, &file, sizeof(DllFile), &n, NULL);
//		}
//		else
//		{
//			cout << "No such files";
//			break;
//		}
//	}
//	CloseHandle(hFile);
//	hFile = CreateFile(_TEXT("c:\\FIND\\find.dat"), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	DllFile ff;
//	for (int i = 0; i < 15; i++)
//	{
//		ReadFile(hFile, &ff, sizeof(DllFile), &n, NULL);
//		_tprintf(_T("Contain of find.dat: %s \t\t"), ff.FileName);
//		_tprintf(_T("time: %d  "), ff.CreationTime.wHour);
//		_tprintf(_T("%d \n"), ff.CreationTime.wMinute);
//	}
//	CloseHandle(hFile);
//	system("pause");
//	return 0;
//}

