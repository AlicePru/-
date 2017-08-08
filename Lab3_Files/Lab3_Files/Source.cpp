#include <iostream>
#include <iomanip>
#include <Windows.h>
#pragma warning(disable : 4996)

using namespace std;
void DisplayBits(unsigned int value);
void compare(OSVERSIONINFO osInfo, DWORD dwMajorVersion, DWORD dwMinorVersion);
void typeCompare(TCHAR *disk);
 
void main()
{
	//OS Version
	OSVERSIONINFO osInfo;//переменная типа,которая хранит поля отвечающие за версию,платформу и тд.
	ZeroMemory(&osInfo, sizeof(osInfo));//обнуляет память. очищает память от мусора ,который может храниться в созданном классе. 
	osInfo.dwOSVersionInfoSize = sizeof(osInfo);
	//cout << osInfo.dwOSVersionInfoSize;
	GetVersionEx(&osInfo);
	cout << "Id Operation System "<< osInfo.dwMajorVersion<<endl;
	cout << "Id Version          " << osInfo.dwMinorVersion << endl;
	cout << "Id Platform         " << osInfo.dwPlatformId << endl;
	cout << "Operation System on This Computer: ";
	compare(osInfo, osInfo.dwMajorVersion, osInfo.dwMinorVersion);

	//Comp Name
	char name[30];
	DWORD size;
	size = sizeof(name);
	GetComputerName(name, &size);
	cout << "Computer name:      " << name << endl;

	//Local Time and Timezone
	SYSTEMTIME t;
	GetLocalTime(&t);
	cout << "Local Time:         " << t.wHour << ":" << t.wMinute << ":" << t.wSecond<<endl;
	TIME_ZONE_INFORMATION z;
	GetTimeZoneInformation(&z);
	int b = -(z.Bias / 60);
	int db = -(z.DaylightBias/60);
	WCHAR *dn = z.DaylightName;
	cout << "Time Zone: +" << b <<" Daylight time zone: +"<<db<<endl;


	//Users name and languge
	setlocale(LC_ALL, "Russian");
	cout << "Language ID:        "<< GetUserDefaultLangID() << endl;//получает айди языка на компьютере в десятичном виде
	DWORD wLang = GetUserDefaultLangID();
	TCHAR szLang[100];
	DWORD cchLang=100;
	VerLanguageName(wLang,szLang,cchLang);//по айди определяет строковое предста
	cout <<"Language of computer: "<<szLang<<endl;
	char userName [30];
	DWORD size2;
	size2 = MAX_COMPUTERNAME_LENGTH + 1;
	GetUserName(userName, &size2);
	cout << "User name:          " << userName << endl;
	
	//Directories
	TCHAR buff[100];
	GetCurrentDirectory(100, buff);
	cout <<"Current directoty:  "<< buff<<endl;
	UINT uSize=100;
	GetWindowsDirectory(buff, uSize);//директория где хранится ос
	cout <<"Windows directory:  "<< buff << endl;
	GetSystemDirectory(buff, uSize);//директория где хранятся системные файлы и драйвера
	cout <<"System directory:   " << buff << endl;

	//Disks
	int ld = GetLogicalDrives();//получает драйвера в виде десятичнго числа. т.е если смотреть на 32 битное представление,мы увидим 1 включеные в битах,отвечающих за диск.
	cout << "Logical drives in binary format: " << ld << endl;
	DisplayBits(ld);

	

	DWORD lpTotalNumberOfClusters[100],
		lpSectorsPerCluster[100],
		lpBytesPerSector[100],
		lpNumberOfFreeClusters[100];
	TCHAR ldName[100];
	GetLogicalDriveStrings(100, ldName);//заполнит буфер текстовыми строками

	TCHAR *disk;
	disk = ldName;
	cout << "Names of logical drives on my computer: "<<endl;
	while (*disk)
	{
		ULARGE_INTEGER free;
		GetDiskFreeSpaceEx(disk, &free, NULL, NULL);
		GetDriveType(disk);
		cout <<disk << " Free space on disk: " <<free.QuadPart<<" Byte"<< " Drive type: ";
		typeCompare(disk);
		disk = disk + sizeof(disk) ;
	}

	//LPCTSTR cName = "C:\\ ";
	//GetDiskFreeSpace(NULL, lpSectorsPerCluster, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters);
	//unsigned int fc = int(lpNumberOfFreeClusters)*int(lpSectorsPerCluster)*int(lpBytesPerSector);
	//cout << "Free space on disk C: " << fc << endl;
	////cout << "Sectors in cluster:" << int(lpSectors) << "\nBytes in sector: " << int(lpBytes) << "\nNumber of free clusters" << int(lpNumClust) << "\nTotal number of clusters:" << int(lpTotNumClust) << endl;
	//
	////LPCTSTR dName = "D:\\ ";
	//GetDiskFreeSpace("D:\ ",lpSectorsPerCluster, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters);
	//unsigned int fd = int(lpNumberOfFreeClusters)*int(lpSectorsPerCluster)*int(lpBytesPerSector);
	//cout << "Free space on disk D: " << fd << endl;
	////cout << "Sectors in cluster:" << int(lpSectors) << "\nBytes in sector: " << int(lpBytes) << "\nNumber of free clusters" << int(lpNumClust) << "\nTotal number of clusters:" << int(lpTotNumClust) << endl;



	
	system("pause");
}

void DisplayBits(unsigned int value)
{
	unsigned int c = 0;
	unsigned int displayMask = 1 << 31;
	for (c = 1; c <= 32; c++)
	{
		cout << (value & displayMask ? '1' : '0');
		displayMask >>= 1;
		if (c % 8 == 0)
		{
			cout << ' ';
		}
	}
	cout << endl;
}

void compare(OSVERSIONINFO osInfo,DWORD dwMajorVersion,DWORD dwMinorVersion)
{
	if (osInfo.dwMajorVersion == 10 & osInfo.dwMinorVersion == 0)
		cout << "Windows 10" << endl;
	if (osInfo.dwMajorVersion == 6 & osInfo.dwMinorVersion == 3)
		cout << "Windows 8.1" << endl;
	if (osInfo.dwMajorVersion == 6 & osInfo.dwMinorVersion == 2)
		cout << "Windows 8" << endl;
	if (osInfo.dwMajorVersion == 6 & osInfo.dwMinorVersion == 1)
		cout << "Windows 7" << endl;
	if (osInfo.dwMajorVersion == 6 & osInfo.dwMinorVersion == 0)
		cout << "Windows Server 2008" << endl;
	if (osInfo.dwMajorVersion == 5 & osInfo.dwMinorVersion ==2)
		cout << "Windows Server 2003" << endl;
	if (osInfo.dwMajorVersion == 5 & osInfo.dwMinorVersion == 1)
		cout << "Windows XP" << endl;
	if (osInfo.dwMajorVersion == 5 & osInfo.dwMinorVersion == 0)
		cout << "Windows 2000" << endl;
}

void typeCompare(TCHAR *disk)
{
	if (GetDriveType(disk) == 0)
		cout << "Drive unknown" << endl;
	if (GetDriveType(disk) == 1)
		cout << "Drive is no root dir" << endl;
	if (GetDriveType(disk) == 2)
		cout << "Drive is removable" << endl;
	if (GetDriveType(disk) == 3)
		cout << "Drive is fixed" << endl;
	if (GetDriveType(disk) == 4)
		cout << "Drive is remote" << endl;
	if (GetDriveType(disk) == 5)
		cout << "Drive is CDROM" << endl;
	if (GetDriveType(disk) == 6)
		cout << "Drive is RAM" << endl;

}
