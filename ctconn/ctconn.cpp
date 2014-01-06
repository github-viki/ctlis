// ctconn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if (WaitNamedPipe("\\\\.\\pipe\\CTLIS1", NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		printf(" wair error %d \n",GetLastError());
		return -1;
	}
	HANDLE hPipe = CreateFile("\\\\.\\pipe\\CTLIS1", GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		printf("error\n");
		return -1;
	}
	
	else
	{
		printf("open suc\n");
	}
	// 向管道写入数据
	DWORD WriteNum=0;
	char buf[10]={"abcs"};
	if (WriteFile(hPipe, buf, strlen(buf), 
		&WriteNum, NULL) == FALSE)
	{
		MessageBox(NULL,"oo","write",0);
		return -1;
	} else {
		MessageBox(NULL,"suc","write",0);
		
	}
	CloseHandle(hPipe); // 关闭管道句柄
	return 0;
}

