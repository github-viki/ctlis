// ctnext.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hPipe=(HANDLE)argv[1];
	char buffer[1024]={'0'};
	DWORD ReadNum=0;
	if(ReadFile(hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE)
	{
		CloseHandle(hPipe); // �رչܵ����
		printf("�ӹܵ���ȡ����ʧ��!"); // ��ʾ��Ϣ
		MessageBox(NULL,"oo","NEXE",0);
		return -1;
	} 
	buffer[ReadNum]='\0';
	MessageBox(NULL,"oo",buffer,0);
	return 0;
}

