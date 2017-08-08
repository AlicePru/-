#include<iostream>
#include<windows.h>
#include<tchar.h>
#include<stdio.h>
HKEY KeysNames(int keyID,char *);

using namespace std;
int main()
{
	HKEY hKey;
	int keyID;
	char lpSubKey[MAX_PATH];
	cout << "                  PLEASE ENTER ONE OF DESIRABLE ROOT KEY'S ID: "<<endl;
	cout << "For HKEY_CLASSES_ROOT  - 0" << endl;
	cout << "For HKEY_CURRENT_CONFIG- 1" << endl;
	cout << "For HKEY_CURRENT_USER  - 2" << endl;
	cout << "For HKEY_LOCAL_MACHINE - 3" << endl;
	cout << "For HKEY_USERS         - 4" << endl;
	cin >> keyID;
	cout << "                                            Enter the SUBKEY : "<<endl;
	cin >> lpSubKey;
	hKey=KeysNames(keyID,lpSubKey);

	DWORD lpcSubKeys,
	      MaxSubKeyLen,
	      Values,
	      MaxValueNameLen,
	      MaxValueLen;

	/*ZeroMemory(&keys, sizeof(DWORD));
	ZeroMemory(&MaxSubKeyLen, sizeof(DWORD));
	ZeroMemory(&values, sizeof(DWORD));
	ZeroMemory(&MaxValueNamelen, sizeof(DWORD));
	ZeroMemory(&MaxValueLen, sizeof(DWORD));*/
	LONG result = RegQueryInfoKey(hKey, NULL, NULL, NULL, &lpcSubKeys, &MaxSubKeyLen, NULL, &Values,&MaxValueNameLen, &MaxValueLen, NULL, NULL);

	TCHAR subKeyName[50];
	DWORD buff;
	TCHAR buffer[MAX_PATH];
	DWORD bufSize = MAX_PATH;
	for (int i = 0; i < Values; i++)
	{
		RegEnumValue(hKey, i, subKeyName, &buff, NULL, NULL, NULL, NULL);
			RegGetValue(hKey, NULL, (LPCTSTR)&subKeyName, RRF_RT_ANY, 0, &buffer, &bufSize);
			/*_tprintf(TEXT("%s -> "), subKeyName);
			_tprintf(TEXT("Value: %s"), buffer);*/
			cout << "Name of SubSubkey: " << subKeyName << endl;
			cout << " Value: " << buffer<<endl;
	}

	RegCloseKey(hKey);

	system("pause");
	return 0;
}

HKEY KeysNames(int keyID, char *lpSubKey)
{
	HKEY hKey=0;
	LONG open;
	switch (keyID)
	{
	case 0:
	{
		open = RegOpenKeyEx(HKEY_CLASSES_ROOT, lpSubKey, 0, KEY_READ, &hKey);
		break;
	}
	case 1:
	{
		open = RegOpenKeyEx(HKEY_CURRENT_CONFIG, lpSubKey, 0, KEY_READ, &hKey);
		break;
	}
	case 2:
	{
		open = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ, &hKey);
		break;
	}
	case 3:
	{
		open = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey);
		break;
	}
	case 4:
	{
		open = RegOpenKeyEx(HKEY_USERS, lpSubKey, 0, KEY_READ, &hKey);
		break;
	}
	}
	if (open == ERROR_SUCCESS)
	{
		cout << "                          REGISTER IS OPENED SUCCSESSFULY!" << endl;
	}
	else
	{
		cout << "                                 REGISTER IS NOT OPENED!" << endl;
	}

	return hKey;
}