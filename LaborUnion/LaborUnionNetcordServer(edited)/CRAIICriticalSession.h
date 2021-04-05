#pragma once
#include <Windows.h>
#include "Defines.h"

class CRAIICriticalSession
{
private:
	CRITICAL_SECTION* m_lpcrit;

public:
	CONSTRUCTOR CRAIICriticalSession(CRITICAL_SECTION crit);
	DESTRUCTOR	~CRAIICriticalSession();
};