#include "pch.h"
#include "CriticalG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCriticalG::CCriticalG(void)
{
	InitializeCriticalSection(&m_cs);
}

CCriticalG::~CCriticalG(void)
{
	DeleteCriticalSection(&m_cs);
}

void CCriticalG::Lock(void)
{
	EnterCriticalSection(&m_cs);
}

void CCriticalG::UnLock(void)
{
	LeaveCriticalSection(&m_cs);
}
LONG CCriticalG::GetLockCount()
{
	return m_cs.LockCount;
}