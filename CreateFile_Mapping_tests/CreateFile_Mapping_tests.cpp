#include <windows.h> 
#include <string> 
#include <winbase.h> 
#include <iostream> 
using namespace std;

/* Example from: https://sqlserverscribbles.com/2013/05/25/createfilemapping-or-mapviewoffileex-example/ */
void main(int argc, char** argv)
{
	HANDLE  h;

	CHAR *filename;

	if (argc < 2) {
		filename = new CHAR[2500];
		wcout << "enter the file name:";
		cin.getline(filename, 2500);
	}
	else {
		filename = argv[1];
	}

	//h = CreateFile(filename, 0xC0010000, 0x00000007, NULL, 0x00000003, 0x40000000, 0x00000000); // -> No read nor write access
	//h = CreateFile(filename, 0xC0000000, 0x00000007, NULL, 0x00000003, 0x40000000, 0x00000000); // -> Read access for hex workshop and notepad but not for HxD?_?
	//h = CreateFile(filename, NULL, 0x00000007, NULL, 0x00000003, 0x40000000, 0x00000000); // -> Read and Write access for all
	h = CreateFile(filename, NULL, 0x00000007, NULL, 0x00000001, 0x40000000, 0x00000000); // -> Read and Write access for all
	cout << filename;
	if (h != INVALID_HANDLE_VALUE)
	{
		printf("\nFile is opened/created\n");
		DWORD size = GetFileSize(h, NULL);
		HANDLE hFileMapping = CreateFileMapping(h, NULL, 0x00000004, 0, 0x00002000, 0x00000000);

		//CloseHandle(h);

		MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
		system("Pause");

		UnmapViewOfFile(hFileMapping);
	}
	else
	{
		printf("\nUnable to open or create file\n");
	}
	system("pause");

}
