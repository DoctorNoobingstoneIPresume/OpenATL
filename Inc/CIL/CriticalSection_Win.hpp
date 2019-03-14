#ifndef CIL_CRITICALSECTION_WIN_HPP
#define CIL_CRITICALSECTION_WIN_HPP 1


#include "Windows.hpp"

// [2016-08-16] For DMC, <cstdlib> does not memset in namespace std.
#include <stdlib.h>


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComCriticalSection
{
private:
	CRITICAL_SECTION m_sec;
	
private:
	CComCriticalSection
	(const CComCriticalSection &rhs);
	
	CComCriticalSection &
	operator=
	(const CComCriticalSection &rhs);

public:
	~CComCriticalSection
	()
	CIL_NOTHROW
	{}
	
	CComCriticalSection
	()
	CIL_NOTHROW
	{
		memset (&m_sec, 0, sizeof (m_sec));
	}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		// [2016-08-16] TODO: We might want to check whether a Windows structured exception is raised.
		InitializeCriticalSection (&m_sec);
		return S_OK;
	}
	
	HRESULT
	Term
	()
	CIL_NOTHROW
	{
		DeleteCriticalSection (&m_sec);
		return S_OK;
	}
	
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		EnterCriticalSection (&m_sec);
		return S_OK;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		LeaveCriticalSection (&m_sec);
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComAutoCriticalSection
{
private:
	CRITICAL_SECTION m_sec;
	
private:
	CComAutoCriticalSection
	(const CComAutoCriticalSection &rhs);
	
	CComAutoCriticalSection &
	operator=
	(const CComAutoCriticalSection &rhs);
	
public:
	~CComAutoCriticalSection
	()
	{
		DeleteCriticalSection (&m_sec);
	}
	
	CComAutoCriticalSection
	()
	{
		memset (&m_sec, 0, sizeof (m_sec));
		
		// [2016-08-16] TODO: We might want to check whether a Windows structured exception is raised.
		InitializeCriticalSection (&m_sec);
	}
	
	
public:
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		EnterCriticalSection (&m_sec);
		return S_OK;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		LeaveCriticalSection (&m_sec);
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComSafeDeleteCriticalSection
{
private:
	CRITICAL_SECTION m_sec;
	bool             m_bInitialized;
	
private:
	CComSafeDeleteCriticalSection
	(const CComSafeDeleteCriticalSection &rhs);
	
	CComSafeDeleteCriticalSection &
	operator=
	(const CComSafeDeleteCriticalSection &rhs);
	
public:
	~CComSafeDeleteCriticalSection
	()
	CIL_NOTHROW
	{
		if (m_bInitialized)
		{
			// [2016-08-16] TODO:
			//   In ATL, the assignment to m_bInitialized is performed before the call to DeleteCriticalSection
			//   and, more importantly, it actually is performed.
			//   Currently, we choose not to perform it.
			//   We should consider whether this choice has bad implications.
			
			DeleteCriticalSection (&m_sec);
			//m_bInitialized = false;
		}
	}
	
	CComSafeDeleteCriticalSection
	()
	CIL_NOTHROW
		: m_bInitialized (false)
	{
		memset (&m_sec, 0, sizeof (m_sec));
	}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (! m_bInitialized);
		
		// [2016-08-16] TODO:
		//   We might want to check whether a Windows structured exception is raised.
		InitializeCriticalSection (&m_sec);
		m_bInitialized = true;
		
		return S_OK;
	}
	
	HRESULT
	Term
	()
	CIL_NOTHROW
	{
		if (m_bInitialized)
		{
			// [2016-08-16] TODO:
			//   In ATL, the assignment to m_bInitialized is performed before the call to DeleteCriticalSection.
			//   Currently, we choose to perfom it after.
			//   We should consider whether this choice has bad implications.
			
			DeleteCriticalSection (&m_sec);
			m_bInitialized = false;
		}
		
		return S_OK;
	}
	
	// [2016-08-16] TODO:
	//   In ATL, this function is not declared as "throwing nothing".
	//   Currently, we choose to do the same.
	HRESULT
	Lock
	()
	{
		CIL_ASSERT (m_bInitialized);
		
		EnterCriticalSection (&m_sec);
		
		return S_OK;
	}
	
	// [2016-08-16] TODO:
	//   In ATL, this function is not declared as "throwing nothing".
	//   Currently, we choose to do the same.
	HRESULT
	Unlock
	()
	{
		CIL_ASSERT (m_bInitialized);
		
		LeaveCriticalSection (&m_sec);
		
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// ...
// 
// [2016-08-16] TODO:
//   This is the same as CComSafeDeleteCriticalSection without Term.
//   The TODO notes there apply here as well.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComAutoDeleteCriticalSection
{
private:
	CRITICAL_SECTION m_sec;
	bool             m_bInitialized;
	
private:
	CComAutoDeleteCriticalSection
	(const CComAutoDeleteCriticalSection &rhs);
	
	CComAutoDeleteCriticalSection &
	operator=
	(const CComAutoDeleteCriticalSection &rhs);
	
public:
	~CComAutoDeleteCriticalSection
	()
	CIL_NOTHROW
	{
		if (m_bInitialized)
			DeleteCriticalSection (&m_sec);
	}
	
	CComAutoDeleteCriticalSection
	()
	CIL_NOTHROW
		: m_bInitialized (false)
	{
		memset (&m_sec, 0, sizeof (m_sec));
	}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (! m_bInitialized);
		
		InitializeCriticalSection (&m_sec);
		m_bInitialized = true;
		
		return S_OK;
	}
	
	HRESULT
	Lock
	()
	{
		CIL_ASSERT (m_bInitialized);
		
		EnterCriticalSection (&m_sec);
		
		return S_OK;
	}
	
	HRESULT
	Unlock
	()
	{
		CIL_ASSERT (m_bInitialized);
		
		LeaveCriticalSection (&m_sec);
		
		return S_OK;
	}

};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
