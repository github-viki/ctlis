#pragma once;  

//�ú������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)����  
//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)����  
//��DLL_IMPLEMENT��simpledll.cpp�ж���  
#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  
#else  
#define DLL_API __declspec(dllimport)  
#endif 
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <windows.h>
#include <stdarg.h>
extern   "C"__declspec(dllexport) int wlog(const char *path,bool writetime,const char *forMat,...);