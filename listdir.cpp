#include "windows.h"
#pragma warning( disable : 4996)

static int count;



int _tmain(int argc, wchar_t* argv[]) {
    	wchar_t s[512];              	// ������� �����
    	GetCurrentDirectory(512, s);	// �������� ������� �����
    	wprintf(TEXT("Starting in: %s\n"), s);

    	count = 0;                  	// �������� ������� ������    	

        //dfs();                     	// ��������� ����� � �������
   	 
    	wprintf(TEXT("File count = %d\n"), count);
    	return 0;
}


/*void dfs() {
	HANDLE hFind;                   	// ����� ������
	WIN32_FIND_DATA res;            	// ��������� ������

	CHAR dir[] = ".\\*";
	hFind = FindFirstFile(dir, &res);   // ����� ������ ����

	do {
    	count++; // ��������� ����� �� ���������??
    	_tprintf(TEXT("file #%d is <%s>\n"), count, res.cFileName);

    	// ...
    	// ����� ����� ����� � �������
	} while (FindNextFile(hFind, &res) != 0);
	FindClose(hFind);
}
*/
