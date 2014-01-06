// ctlis.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "simpleDll.h"
#pragma comment(lib,"simpleDll.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR lpChUserName[128]={'0'};
	DWORD dSize=128;
	if(!GetUserName(lpChUserName,&dSize))
	{
		wlog("CloudTerm\\cthandler.log",true,"%s:GetUserName %d\n",argv[0],GetLastError());
		return -1;
	}
	TCHAR lpChPipeName[128]={'0'};
	sprintf(lpChPipeName,"\\\\.\\pipe\\CTLIS%s",lpChUserName);
	wlog("CloudTerm\\cthandler.log",true,"%s\n",lpChPipeName);
	HANDLE hPipe;
	
	hPipe=CreateNamedPipe(
		lpChPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE,
		PIPE_UNLIMITED_INSTANCES,
		1024,
		1024,
		NMPWAIT_WAIT_FOREVER,
		NULL
		);
	if(hPipe==INVALID_HANDLE_VALUE)
	{
		wlog("CloudTerm\\cthandler.log",true,"%s:create named pipe %d\n",argv[0],GetLastError());
		return -1;
	}

	while(1)
	{

	if (ConnectNamedPipe(hPipe,NULL)==false)
	{
		wlog("CloudTerm\\cthandler.log",true,"%s:wait %d\n",argv[0],GetLastError());
		return -1;
	}
	char buffer[1024]={'0'};
	DWORD ReadNum=0;

	if(ReadFile(hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE)
	{
		 CloseHandle(hPipe); // �رչܵ����
		wlog("CloudTerm\\cthandler.log",true,"%s:read error %d\n",argv[0],GetLastError());// ��ʾ��Ϣ
		continue;
	} 
	//CloseHandle(hPipe);
		DisconnectNamedPipe(hPipe);
		 buffer[ReadNum] = '\0'; // ��ʾ���յ�����Ϣ
		 printf("%s\n",buffer);
		 wlog("CloudTerm\\cthandler.log",true,"	%s:read %s\n",argv[0],buffer);
		 char cmd[128]={'0'};
		 STARTUPINFO si;
		 PROCESS_INFORMATION pi;
		 ZeroMemory(&si, sizeof(si));
		 si.cb = sizeof(si);
		 ZeroMemory(&pi, sizeof(pi));
		 sprintf(cmd,"caccthandler.exe %s\n",buffer);
		 if( !CreateProcess( NULL,   // No module name (use command line)
			 const_cast <char *>(cmd),        // Command line
			 NULL,           // Process handle not inheritable
			 NULL,           // Thread handle not inheritable
			 FALSE,          // Set handle inheritance to FALSE
			 NULL,              // No creation flags
			 NULL,           // Use parent's environment block
			 NULL,           // Use parent's starting directory 
			 &si,            // Pointer to STARTUPINFO structure
			 &pi )           // Pointer to PROCESS_INFORMATION structure
			 ) 
		 {
			 MessageBox(NULL,"�������Ӳ�ͨ","ctlis",0);
			 continue;
		 }
		 else
		 {
			 CloseHandle( pi.hProcess );
			 CloseHandle( pi.hThread );
		 }
		 
	}
	return 0;
}
//modify the ctlis
