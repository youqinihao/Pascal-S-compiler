// startcompile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<windows.h>

int main(int argc, char* argv[])
{
	char file[200];
	if(argc==1){
	printf("please input the source file name included the filepath name:\n");
	scanf("%s",file);
	}
	else
		strcpy(file,argv[1]);	
	typedef void (*pMyFun)(char *file);
	HINSTANCE hDll;
	pMyFun compiler;
	hDll=::LoadLibrary("mycompiler.dll");
    compiler=(pMyFun)GetProcAddress(hDll,"compiler");
    compiler(file);
	system("pause");
	FreeLibrary(hDll);
	return 0;
}
