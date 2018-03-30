#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <TCHAR.h>
#pragma warning( disable : 4996)

static int count;
static long long size;

void dfs() {
	HANDLE hFind;                   	// ����� ������
	WIN32_FIND_DATA res;            	// ��������� ������

	//CHAR dir[] = ".\\*";
	hFind = FindFirstFile(L"*", &res);   // ����� ������ ����

	do {
    	_tprintf(TEXT("<%s>\n"), res.cFileName);

		if ((res.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
		{ // ���� ��� ��������
			if ((wcscmp(res.cFileName, L"..")==0)| (wcscmp(res.cFileName, L".") == 0)) continue;
		   //����� ����� ����� � �������
			_tprintf(TEXT("====<%s>====\n"), res.cFileName);
			SetCurrentDirectory(res.cFileName);
			dfs();
			//SetCurrentDirectory(L"..");
		}
		else 
		{// ��� ����
			count++;
			_tprintf(TEXT("file #%d is <%s> \n"), count, res.cFileName);
			
			size += (LONGLONG(res.nFileSizeHigh) * (LONGLONG(MAXDWORD) + LONGLONG(1)) + LONGLONG(res.nFileSizeLow));
			//size += ((res.nFileSizeHigh * 4294967296) + res.nFileSizeLow);
		}
	} while (FindNextFile(hFind, &res) != 0);
		FindClose(hFind);
		SetCurrentDirectory(L"..");
}

int main() {
    	wchar_t s[512];              	// ������� �����
    	GetCurrentDirectory(512, s);	// �������� ������� �����
    	wprintf(L"Starting in: %s\n", s);

    	count = 0;                  	// �������� ������� ������    	
		size = 0;
		/*
		HANDLE hFind;
		WIN32_FIND_DATA fileinfo;
		hFind=FindFirstFile(L"*", &fileinfo);
		do {
    	count++; // ��������� ����� �� ���������??
		wprintf(L"file #%d is <%s>\n", count, fileinfo.cFileName);

    	// ...
    	// ����� ����� ����� � �������
		} while (FindNextFile(hFind, &fileinfo) != 0);
	FindClose(hFind);
		wprintf(L"%s\n",fileinfo.cFileName);

    	wprintf(L"File count = %d\n", count);
    	*/
		
        dfs();                     	// ��������� ����� � �������
   		printf("File count = %d, size = %lld\n", count, size);
		printf("DW = %lld, DW+1 = %lld\n", LONGLONG(MAXDWORD), LONGLONG(4294967296));
		scanf("%D", &count);
		return 0;
}



