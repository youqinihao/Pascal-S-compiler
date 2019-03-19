// startinterpret.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<windows.h>


void main(int argc ,char **argv){
	char file[200];
	if(argc==1){
		printf("请出入二进制p代码文件名:\n");
		scanf("%s",file);
	}
    else
		strcpy(file,argv[1]);
	typedef void (*pMyFun)(char *file);
	HINSTANCE hDll;
	pMyFun interpreter;
	hDll=::LoadLibrary("myinterpreter.dll");
    interpreter=(pMyFun)GetProcAddress(hDll,"interpreter");
    interpreter(file);
	FreeLibrary(hDll);

}