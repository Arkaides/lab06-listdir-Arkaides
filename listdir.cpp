#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <TCHAR.h>
#pragma warning( disable : 4996)

static int count;
static long long size;

void dfs() {
	HANDLE hFind;                   	// номер поиска
	WIN32_FIND_DATA res;            	// результат поиска

	//CHAR dir[] = ".\\*";
	hFind = FindFirstFile(L"*", &res);   // найти первый файл

	do {
    	_tprintf(TEXT("<%s>\n"), res.cFileName);

		if ((res.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
		{ // если это подпапка
			if ((wcscmp(res.cFileName, L"..")==0)| (wcscmp(res.cFileName, L".") == 0)) continue;
		   //здесь будет обход в глубину
			_tprintf(TEXT("====<%s>====\n"), res.cFileName);
			SetCurrentDirectory(res.cFileName);
			dfs();
			//SetCurrentDirectory(L"..");
		}
		else 
		{// это файл
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
    	wchar_t s[512];              	// текущая папка
    	GetCurrentDirectory(512, s);	// получить текущую папку
    	wprintf(L"Starting in: %s\n", s);

    	count = 0;                  	// обнулить счетчик файлов    	
		size = 0;
		/*
		HANDLE hFind;
		WIN32_FIND_DATA fileinfo;
		hFind=FindFirstFile(L"*", &fileinfo);
		do {
    	count++; // некоторые файлы не считаются??
		wprintf(L"file #%d is <%s>\n", count, fileinfo.cFileName);

    	// ...
    	// здесь будет обход в глубину
		} while (FindNextFile(hFind, &fileinfo) != 0);
	FindClose(hFind);
		wprintf(L"%s\n",fileinfo.cFileName);

    	wprintf(L"File count = %d\n", count);
    	*/
		
        dfs();                     	// запустить обход в глубину
   		printf("File count = %d, size = %lld\n", count, size);
		printf("DW = %lld, DW+1 = %lld\n", LONGLONG(MAXDWORD), LONGLONG(4294967296));
		scanf("%D", &count);
		return 0;
}



