// ctnext.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hPipe=(HANDLE)argv[1];
	char buffer[1024]={'0'};
	DWORD ReadNum=0;
	if(ReadFile(hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE)
	{
		CloseHandle(hPipe); // 关闭管道句柄
		printf("从管道读取数据失败!"); // 显示信息
		MessageBox(NULL,"oo","NEXE",0);
		return -1;
	} 
	buffer[ReadNum]='\0';
	MessageBox(NULL,"oo",buffer,0);
	return 0;
}

