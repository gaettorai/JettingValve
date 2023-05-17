#pragma once

class CCriticalG
{
public:
	CCriticalG(void);
	virtual ~CCriticalG(void);

	void Lock(void);
	void UnLock(void);
	LONG GetLockCount();
private:
	CRITICAL_SECTION	m_cs;
};