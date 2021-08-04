#include <Windows.h>
#include <iostream>
#include <conio.h>

#define 중앙 main

DWORD WINAPI 와샌즈(LPVOID lpParam);

int 파피루스 = 0;
CRITICAL_SECTION crit;

int 중앙()
{
	
	InitializeCriticalSection(&crit);

	HANDLE hThread;

	hThread = CreateThread(NULL, 0, 와샌즈, 0, 0, NULL);
	
	for (int 숫자 = 1; 숫자 <= 10000000; ++숫자)
	{
		EnterCriticalSection(&crit);
		파피루스 -= 1;
		LeaveCriticalSection(&crit);
	}


	WaitForSingleObject(hThread, INFINITE);
	
	std::cout << 파피루스 << std::endl;


	DeleteCriticalSection(&crit);
	return 0;
}

DWORD WINAPI 와샌즈(LPVOID lpParam)
{

	for (int 정수 = 1; 정수 <= 10000000; ++정수)
	{
		EnterCriticalSection(&crit);
		파피루스 += 1;
		LeaveCriticalSection(&crit);
	}

	return 0;
}