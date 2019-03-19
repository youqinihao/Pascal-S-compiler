// startmydebug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <stdio.h>


//#pragma comment(lib,"yo.lib")
//extern "C" _declspec(dllimport) int fnYo(int i); 
//extern "C" _declspec(dllimport) int nYo; 
int main(int argc, char* argv[])
{
	
	/*typedef int (*pMyFun)(char *file);
	HINSTANCE hDll;
	pMyFun compiler;
	hDll=::LoadLibrary("mycompiler.dll");
    compiler=(pMyFun)GetProcAddress(hDll,"compiler");
    compiler("c:\\\\mypl.p");
	FreeLibrary(hDll);
	return 0;*/
	char file[200];
	if(argc==1){
	printf("please input the source file name included the filepath name:\n");
	scanf("%s",file);
	}
	else
		strcpy(file,argv[1]);	
	typedef void (*pMyFun)(char *file);
	HINSTANCE hDll;
	pMyFun interpret;
	hDll=::LoadLibrary("mydebug.dll");
    interpret=(pMyFun)GetProcAddress(hDll,"interpret");
    interpret(file);
	FreeLibrary(hDll);
	return 0;
}

