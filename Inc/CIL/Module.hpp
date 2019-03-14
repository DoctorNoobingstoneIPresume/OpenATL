#ifndef CIL_MODULE_HPP
#define CIL_MODULE_HPP 1


#include "ThreadModel.hpp"


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CModule
{
private:
	LONG m_nLockCount;

private:
	CModule
	(const CModule &);
	
	CModule &
	operator=
	(const CModule &);

public:
	~CModule
	()
	{}
	
	CModule
	()
		: m_nLockCount (0)
	{}
	
public:
	ULONG
	Lock
	()
	{
		// [2016-10-17] TODO: An assertion might help us detect a negative count.
		const ULONG nRet = CComGlobalsThreadModel::Increment (&m_nLockCount);
		return nRet;
	}
	
	ULONG
	Unlock
	()
	{
		// [2016-10-17] TODO: An assertion might help us detect a negative count.
		return CComGlobalsThreadModel::Decrement (&m_nLockCount);
	}
	
	ULONG
	GetLockCount
	()
	{
		// [2016-10-10] TODO:
		//   In Windows (and I believe in general for x86), reading an (aligned) integer is an atomic operation.
		//   For other platforms (with GCC), we might wish to use "__gnu_cxx::__exchange_and_add (&m_nLockCount, 0);".
		return m_nLockCount;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// ModuleLockHelper:
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class ModuleLockHelper
{
private:
	ModuleLockHelper
	(const ModuleLockHelper &);
	
	ModuleLockHelper &
	operator=
	(const ModuleLockHelper &);

private:
	CModule *m_pModule;

public:
	~ModuleLockHelper
	()
	{
		m_pModule->Unlock ();
	}
	
	explicit
	ModuleLockHelper
	(CModule *pModule)
		: m_pModule (pModule)
	{
		m_pModule->Lock ();
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

typedef CModule CExeModule;
typedef CModule CDllModule;


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CModule *
AdrModule
();


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
