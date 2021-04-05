#include "CRAIICriticalSession.h"

CONSTRUCTOR CRAIICriticalSession::CRAIICriticalSession(CRITICAL_SECTION crit) : m_lpcrit(&crit)
{
	InitializeCriticalSection(m_lpcrit);
	EnterCriticalSection(m_lpcrit);
}
DESTRUCTOR	CRAIICriticalSession::~CRAIICriticalSession()
{
	LeaveCriticalSection(m_lpcrit);
	DeleteCriticalSection(m_lpcrit);
}