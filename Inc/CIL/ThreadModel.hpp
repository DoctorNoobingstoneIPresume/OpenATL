#ifndef CIL_THREADMODEL_HPP
#define CIL_THREADMODEL_HPP 1


#include "Interlocked.hpp"
#include "CriticalSection.hpp"


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-10-17] Deviation from ATL:
//   I have added the protected destructors
//   (my usual practice for policy classes -- am I turning into a robot ?).
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComSingleThreadModel
{
protected:
	~CComSingleThreadModel
	()
	{}

public:
	typedef CComFakeCriticalSection         CriticalSection;
	typedef CComFakeCriticalSection         AutoCriticalSection;
	typedef CComFakeCriticalSection         AutoDeleteCriticalSection;
	
	typedef CComSingleThreadModel           ThreadModelNoCS;

public:
	static
	ULONG
	CIL_WINAPI
	Increment
	(CIL_INOUT LONG *px)
	CIL_NOTHROW
	{
		return ++*px;
	}
	
	static
	ULONG
	CIL_WINAPI
	Decrement
	(CIL_INOUT LONG *px)
	CIL_NOTHROW
	{
		return --*px;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComMultiThreadModelNoCS
{
protected:
	~CComMultiThreadModelNoCS
	()
	{}

public:
	typedef CComFakeCriticalSection         CriticalSection;
	typedef CComFakeCriticalSection         AutoCriticalSection;
	typedef CComFakeCriticalSection         AutoDeleteCriticalSection;
	
	typedef CComMultiThreadModelNoCS        ThreadModelNoCS;
	
public:
	static
	ULONG
	CIL_WINAPI
	Increment
	(CIL_INOUT LONG *px)
	CIL_NOTHROW
	{
		return InterlockedIncrement (px);
	}
	
	static
	ULONG
	CIL_WINAPI
	Decrement
	(CIL_INOUT LONG *px)
	CIL_NOTHROW
	{
		return InterlockedDecrement (px);
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CComMultiThreadModel
{
protected:
	~CComMultiThreadModel
	()
	{}

public:
	typedef CComCriticalSection             CriticalSection;
	typedef CComAutoCriticalSection         AutoCriticalSection;
	typedef CComAutoDeleteCriticalSection   AutoDeleteCriticalSection;
	
	typedef CComMultiThreadModelNoCS        ThreadModelNoCS;
	
public:
	static
	ULONG
	CIL_WINAPI
	Increment
	(CIL_INOUT LONG *px)
	{
		return InterlockedIncrement (px);
	}
	
	static
	ULONG
	CIL_WINAPI
	Decrement
	(CIL_INOUT LONG *px)
	{
		return InterlockedDecrement (px);
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// ...
// 
// [2016-10-10] TODO:
//   We might wish to support other scenarios besides the "free threaded" one.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

typedef CComMultiThreadModel CComObjectThreadModel;
typedef CComMultiThreadModel CComGlobalsThreadModel;


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
