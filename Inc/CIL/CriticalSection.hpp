#ifndef CIL_CRITICALSECTION_HPP
#define CIL_CRITICALSECTION_HPP 1


#if defined (_WIN32)
	#include "CriticalSection_Win.hpp"
#else
	#include "CriticalSection_Psx.hpp"
#endif


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComFakeCriticalSection
{
private:
	CComFakeCriticalSection
	(const CComFakeCriticalSection &);
	
	CComFakeCriticalSection &
	operator=
	(const CComFakeCriticalSection &);
	
public:
	~CComFakeCriticalSection
	()
	{}
	
	CComFakeCriticalSection
	()
	{}
	
public:
	HRESULT
	Init
	()
	CIL_NOTHROW
	{
		return S_OK;
	}
	
	HRESULT
	Term
	()
	CIL_NOTHROW
	{
		return S_OK;
	}
	
	HRESULT
	Lock
	()
	CIL_NOTHROW
	{
		return S_OK;
	}
	
	HRESULT
	Unlock
	()
	CIL_NOTHROW
	{
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
