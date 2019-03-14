#ifndef CIL_CRITICALSECTION_PSX_HPP
#define CIL_CRITICALSECTION_PSX_HPP 1


#include "Windows.hpp"

#include <cstring>

#include <pthread.h>


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-08-17] TODO:
//   We might want to translate
//   int error codes from the pthread library to HRESULT error codes.
//   Currently, we are translating any non-zero code to E_FAIL.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComCriticalSection
{
private:
	pthread_mutex_t m_mtx;
	
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
		std::memset (&m_mtx, 0, sizeof (m_mtx));
	}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_init (&m_mtx, 0);
		if (iResult)
			return E_FAIL;
	}
	
	HRESULT
	Term
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_destroy (&m_mtx);
		static_cast <void> (iResult);
		
		return S_OK;
	}
	
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_lock (&m_mtx);
		if (iResult)
			return E_FAIL;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_unlock (&m_mtx);
		if (iResult)
			return E_FAIL;
		
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComAutoCriticalSection
{
private:
	pthread_mutex_t m_mtx;
	
private:
	CComAutoCriticalSection
	(const CComAutoCriticalSection &rhs);
	
	CComAutoCriticalSection &
	operator=
	(const CComAutoCriticalSection &rhs);
	
public:
	~CComAutoCriticalSection
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_destroy (&m_mtx);
		static_cast <void> (iResult);
	}
	
	CComAutoCriticalSection
	()
	{
		std::memset (&m_mtx, 0, sizeof (m_mtx));
		
		{
			const int iResult = pthread_mutex_init (&m_mtx, 0);
			if (iResult)
				throw iResult;
		}
	}
	
public:
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_lock (&m_mtx);
		if (iResult)
			return E_FAIL;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		const int iResult = pthread_mutex_unlock (&m_mtx);
		if (iResult)
			return E_FAIL;
		
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComSafeDeleteCriticalSection
{
private:
	pthread_mutex_t m_mtx;
	bool            m_bInitialized;
	
private:
	CComSafeDeleteCriticalSection
	(const CComSafeDeleteCriticalSection &);
	
	CComSafeDeleteCriticalSection &
	operator=
	(const CComSafeDeleteCriticalSection &);
	
public:
	~CComSafeDeleteCriticalSection
	()
	CIL_NOTHROW
	{
		if (m_bInitialized)
		{
			const int iResult = pthread_mutex_destroy (&m_mtx);
			static_cast <void> (iResult);
		}
	}
	
	CComSafeDeleteCriticalSection
	()
	CIL_NOTHROW
		: m_bInitialized (false)
	{
		std::memset (&m_mtx, 0, sizeof (m_mtx));
	}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (! m_bInitialized);
		
		const int iResult = pthread_mutex_init (&m_mtx, 0);
		if (iResult)
			return E_FAIL;
		
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
			const int iResult = pthread_mutex_destroy (&m_mtx);
			static_cast <void> (iResult);
			
			m_bInitialized = false;
		}
		
		return S_OK;
	}
	
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (m_bInitialized);
		
		const int iResult = pthread_mutex_lock (&m_mtx);
		if (iResult)
			return E_FAIL;
		
		return S_OK;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (m_bInitialized);
		
		const int iResult = pthread_mutex_unlock (&m_mtx);
		if (iResult)
			return E_FAIL;
		
		return S_OK;
	}

};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComAutoDeleteCriticalSection
{
private:
	pthread_mutex_t m_mtx;
	bool            m_bInitialized;
	
private:
	CComAutoDeleteCriticalSection
	(const CComAutoDeleteCriticalSection &);
	
	CComAutoDeleteCriticalSection &
	operator=
	(const CComAutoDeleteCriticalSection &);
	
public:
	~CComAutoDeleteCriticalSection
	()
	CIL_NOTHROW
	{
		if (m_bInitialized)
		{
			const int iResult = pthread_mutex_destroy (&m_mtx);
			static_cast <void> (iResult);
		}
	}
	
	CComAutoDeleteCriticalSection
	()
	CIL_NOTHROW
		: m_bInitialized (false)
	{
		std::memset (&m_mtx, 0, sizeof (m_mtx));
	}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (! m_bInitialized);
		
		const int iResult = pthread_mutex_init (&m_mtx, 0);
		if (iResult)
			return E_FAIL;
		
		m_bInitialized = true;
		return S_OK;
	}
	
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (m_bInitialized);
		
		const int iResult = pthread_mutex_lock (&m_mtx);
		if (iResult)
			return E_FAIL;
		
		return S_OK;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		CIL_ASSERT (m_bInitialized);
		
		const int iResult = pthread_mutex_unlock (&m_mtx);
		if (iResult)
			return E_FAIL;
		
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
