#ifndef CIL_OBJECT_HPP
#define CIL_OBJECT_HPP 1


#include "Module.hpp"
#include "GuidDef.hpp" // [2016-12-29 :x] For InlineIsEqualUnknown.

#include <climits>


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

typedef
	HRESULT
	(CIL_WINAPI _CREATORARGFUNCTION)
	(void *pvThis, REFIID iid, void **ppvInterface, DWORD_PTR dw);


struct _INTMAP_ENTRY
{
	const IID                 *piid;
	      DWORD_PTR            dw;
	      _CREATORARGFUNCTION *pFunc;
};


#if defined (__BORLANDC__)
	#define _SIMPLEMAPENTRY (reinterpret_cast <CIL::_CREATORARGFUNCTION *> (1))
#else
	const _CREATORARGFUNCTION *const _SIMPLEMAPENTRY = reinterpret_cast <_CREATORARGFUNCTION *> (1);
#endif


// [2016-12-29 :x] TODO:
//   In ATL, this function is defined in <AtlBase.h>. Should we put it to "Base.hpp" ?
inline
HRESULT
CIL_WINAPI
InternalQueryInterface
(void *pvThis, const _INTMAP_ENTRY *pEntry, REFIID iid, void **ppvInterface)
{
	// [2016-12-29 :x] Deviation from ATL: A crash might be a better outcome.
	CILASSERT (pvThis);
	//if (! pvThis)
	//	return E_INVALIDARG;
	
	// [2016-12-29 :x] Deviation from ATL: A crash might be a better outcome.
	CILASSERT (pEntry);
	//if (! pEntry)
	//	return E_INVALIDARG;
	
	CILASSERT (pEntry->pFunc == _SIMPLEMAPENTRY);
	
	// [2016-12-29 :x] Deviation from ATL: A crash might be a better outcome.
	//if (! ppvInterface)
	//	return E_POINTER;
	CILASSERT (ppvInterface);
	
	if (CIL::Handy::InlineIsEqualUnknown (iid))
	{
		IUnknown *const pUnk = reinterpret_cast <IUnknown *> (reinterpret_cast <DWORD_PTR> (pvThis) + pEntry->dw);
		pUnk->AddRef ();
		*ppvInterface = pUnk;
		return S_OK;
	}
	else
	{
		for (; ; ++pEntry)
		{
			// [2016-12-29 :x] TODO: I am adding this trap (yup, every time we loop; this can be optimized; mind the calling of pEntry->pFunc !):
			*ppvInterface = 0;
			
			if (! pEntry->pFunc)
				// [2016-12-29 :x] TODO: Mind the trap above:
				//{ *ppvInterface = 0; return E_NOINTERFACE; }
				                     return E_NOINTERFACE;
			
			const bool bBlind = ! pEntry->piid;
			
			if (bBlind || iid == *pEntry->piid)
			{
				if (pEntry->pFunc == _SIMPLEMAPENTRY)
				{
					IUnknown *const pUnk = reinterpret_cast <IUnknown *> (reinterpret_cast <DWORD_PTR> (pvThis) + pEntry->dw);
					pUnk->AddRef ();
					*ppvInterface = pUnk;
					return S_OK;
				}
				else
				{
					const HRESULT hr = pEntry->pFunc (pvThis, iid, ppvInterface, pEntry->dw);
					if (SUCCEEDED (hr))
						return hr;
					
					if (FAILED (hr))
					{
						if (! bBlind)
							{ *ppvInterface = 0; return hr; }
						//else
						//	continue;
					}
					else
					{
						// [2016-12-29 :x] TODO: Investigate this weird style ! Why is only S_OK acceptable ?
						if (hr == S_OK)
							{ CILASSERT (*ppvInterface); return hr; }
						//else
						//	continue;
					}
				}
			}
		}
	}
}


CIL_NAMESPACE_END

	typedef CIL::_CREATORARGFUNCTION _CIL_CREATORARGFUNCTION;
	typedef CIL::_INTMAP_ENTRY _CIL_INTMAP_ENTRY;
	
	#if defined (__BORLANDC__)
		#define _CIL_SIMPLEMAPENTRY _SIMPLEMAPENTRY
	#else
		const CIL::_CREATORARGFUNCTION *const _CIL_SIMPLEMAPENTRY = CIL::_SIMPLEMAPENTRY;
	#endif

CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CComObjectRootBase:
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define CIL_BEGIN_COM_MAP(ComMapClass) \
	\
	typedef ComMapClass _ComMapClass; \
	\
	HRESULT \
	_InternalQueryInterface \
	(REFIID iid, void **ppvInterface) \
	CIL_NOTHROW \
	{ \
		return _ComMapClass::InternalQueryInterface (this, _GetEntries (), iid, ppvInterface); \
	} \
	\
	static \
	const _CIL_INTMAP_ENTRY * \
	CIL_WINAPI \
	_GetEntries \
	() \
	CIL_NOTHROW \
	{ \
		static \
		const _CIL_INTMAP_ENTRY _entries [] = \
		{



#define CIL_END_COM_MAP() \
	\
			{ \
				0, \
				0, \
				0 \
			} \
		}; \
		\
		return _entries; \
	} \
	\
	virtual \
	HRESULT \
	CIL_STDMETHODCALLTYPE \
	QueryInterface \
	(REFIID iid, void **ppvInterface) \
	CIL_NOTHROW \
	= 0; \
	\
	virtual \
	ULONG \
	CIL_STDMETHODCALLTYPE \
	AddRef \
	() \
	CIL_NOTHROW \
	= 0; \
	\
	virtual \
	ULONG \
	CIL_STDMETHODCALLTYPE \
	Release \
	() \
	CIL_NOTHROW \
	= 0;



#define CIL_COM_INTERFACE_ENTRY_IID(iid, Base) \
	\
			{ \
				&(iid), \
				CIL_OFFSETOFCLASS (Base, _ComMapClass), \
				_CIL_SIMPLEMAPENTRY \
			},



#define CIL_COM_INTERFACE_ENTRY_PIID(piid, Base) \
	\
			{ \
				piid, \
				CIL_OFFSETOFCLASS (Base, _ComMapClass), \
				_CIL_SIMPLEMAPENTRY \
			},



class CComObjectRootBase
{
public:
	static
	CModule *
	AdrModule
	()
	{
		return CIL::AdrModule ();
	}
	
public:
	static
	HRESULT
	CIL_WINAPI
	InternalQueryInterface
	(void *pvThis, const _INTMAP_ENTRY *pEntry, REFIID iid, void **ppvInterface)
	{
		CILASSERT (pvThis);
		CILASSERT (pEntry->pFunc == _SIMPLEMAPENTRY);
		
		const HRESULT hr = CIL::InternalQueryInterface (pvThis, pEntry, iid, ppvInterface);
		return hr;
	}

public:
	union
	{
		      LONG      m_dwRef;
		      IUnknown *m_pOuterUnknown;
	};
	
public:
	LONG *
	AdrRefCount
	()
	{
		return &m_dwRef;
	}
	
	const LONG *
	AdrRefCount
	()
	const
	{
		return &m_dwRef;
	}
	
	// [2016-12-05]
	IUnknown **
	AdrOuterUnknownPtr
	()
	{
		return &m_pOuterUnknown;
	}
	
	IUnknown *const *
	AdrOuterUnknownPtr
	()
	const
	{
		return &m_pOuterUnknown;
	}
	
public:
	void
	SetVoid
	(void *)
	{}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CComObjectRootEx (forward declaration(s)):
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class ThreadModel>
class CComObjectRootEx;

template <>
class CComObjectRootEx <CComSingleThreadModel>;


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CComObjectLockT:
// 
// [2016-10-18] Deviation from ATL:
//   The template argument is published (like in CComObjectRootEx).
//   Copying is disabled.
//   The constructor is explicit (and it uses an initializer list).
//   The data member is private.
// 
// [2016-12-29]
//   I think we should avoid embedding a mutex in each object.
//   Therefore, we should avoid CComObjectLockT <...>.
//   We should find another way to implement _Cache (in BEGIN_COM_MAP).
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class ThreadModel>
class CComObjectLockT
{
public:
	typedef ThreadModel                     _ThreadModel;
	typedef CComObjectRootEx <_ThreadModel> _CComObjectRootEx;
	
private:
	CComObjectLockT
	(const CComObjectLockT &);
	
	CComObjectLockT &
	operator=
	(const CComObjectLockT &);
	
public:
	~CComObjectLockT
	()
	{
		if (m_p)
			m_p->Unlock ();
	}
	
public:
	explicit
	CComObjectLockT
	(_CComObjectRootEx *p)
		: m_p (p)
	{
		if (m_p)
			m_p->Lock ();
	}
	
public:
	_CComObjectRootEx *m_p;
};


template <>
class CComObjectLockT <CComSingleThreadModel>
{
public:
	typedef CComSingleThreadModel           _ThreadModel;
	typedef CComObjectRootEx <_ThreadModel> _CComObjectRootEx;
	
private:
	CComObjectLockT
	(const CComObjectLockT &);
	
	CComObjectLockT &
	operator=
	(const CComObjectLockT &);
	
public:
	~CComObjectLockT
	()
	{}
	
private:
	_CComObjectRootEx *_p;
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CComObjectRootEx:
// 
// [2016-10-19] Deviation from ATL:
//   We are not relying on a "LONG m_dwRef;" member variable,
//   but on a "LONG *AdrRefCount ();" member function
//   (as is provided by our version of CComObjectRootBase).
//   TODO: Could this cause incompatibility with... stuff ?
//   On the plus side, one can place a breakpoint there now !
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class ThreadModel>
class CComObjectRootEx
	: public CComObjectRootBase
{
public:
	typedef ThreadModel                                      _ThreadModel;
	typedef typename _ThreadModel::AutoCriticalSection       _CritSec;
	typedef typename _ThreadModel::AutoDeleteCriticalSection _AutoDelCritSec;
	typedef CComObjectLockT <_ThreadModel>                   ObjectLock;
	
private:
	// [2016-12-29 :x] TODO: We might want to make this a private base class sub-object !
	_AutoDelCritSec m_critsec;
	
public:
	ULONG
	InternalAddRef
	()
	{
		CIL_ASSERT (*AdrRefCount () != LONG (-1));
		return _ThreadModel::Increment (AdrRefCount ());
	}
	
	ULONG
	InternalRelease
	()
	{
		const LONG nRet = LONG (_ThreadModel::Decrement (AdrRefCount ()));
		
		#if CIL_DEBUG
		
			if (nRet < - (CIL_INT32_MAX / 2))
				CIL_ASSERT (0 && "InternalRelease: this object was released ages ago.");
		
		#endif
		
		return nRet;
	}
	
	HRESULT
	_AtlInitialConstruct
	()
	{
		return m_critsec.Init ();
	}
};


template <>
class CComObjectRootEx <CComSingleThreadModel>
	: public CComObjectRootBase
{
public:
	typedef CComSingleThreadModel                            _ThreadModel;
	typedef          _ThreadModel::AutoCriticalSection       _CritSec;
	typedef          _ThreadModel::AutoDeleteCriticalSection _AutoDelCritSec;
	typedef CComObjectLockT <_ThreadModel>                   ObjectLock;
	
public:
	HRESULT
	_AtlInitialConstruct
	()
	{
		return S_OK;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CComObject:
// 
// [2016-10-18] Deviation from ATL:
//   The copy constructor is protected.
//   The copy assignment operator is private (and not defined).
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Private
{
	template <typename T>
	class ResetPtrGuard
	{
	public:
		~ResetPtrGuard
		()
		{
			if (_pp)
			{
				// [2016-12-29 :x] Trust me, I know what I am doing !
				// [2016-12-30]    The destructor of CComObject <BaseClass> is now virtual.
				
				//#if defined (__GNUC__)
				//	#pragma GCC diagnostic push
				//	#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
				//#endif
				
				delete *_pp;
				
				//#if defined (__GNUC__)
				//	#pragma GCC diagnostic pop
				//#endif
				
				       *_pp = 0;
			}
		}
		
	private:
		ResetPtrGuard
		(const ResetPtrGuard &);
		
		ResetPtrGuard &
		operator=
		(const ResetPtrGuard &);
		
	public:
		explicit
		ResetPtrGuard
		(T **pp)
			: _pp (pp)
		{}
		
	public:
		T **
		Release
		()
		{
			T **const ppRet = _pp;
			                  _pp = 0;
			return ppRet;
		}
	
	private:
		T **_pp;
	};
}


template <class BaseClass>
class CComObject
	: public BaseClass
{
public:
	typedef BaseClass _BaseClass;

// [2016-12-29] TODO: Deviation from ATL: Should this be used here ?
#if 1
protected:
	CComObject
	(const CComObject &rhs)
		: BaseClass (rhs)
	{}
	
private:
	CComObject &
	operator=
	(CIL_IN const CComObject &rhs);
#endif

public:
	// [2016-10-17] Deviation from ATL:
	//   Versions of ATL up to (and including) 8.0 (at least) do not make the destructor virtual.
	//   Some newer versions make it virtual.
	//   I am going to stick to what I know for now.
	// 
	// [2016-12-30]
	//   But what if somebody creates a class that is derived from CComObject <_BaseClass> ?
	virtual
	~CComObject
	()
	{
		try
		{
			//BaseClass::SetRefCount (- (INT_MAX / 2));
			//BaseClass::FinalRelease ();
			BaseClass::AdrModule ()->Unlock ();
		}
		catch (...)
		{}
	}
	
	explicit
	CComObject
	(void *pvArg = 0)
	{
		static_cast <void> (pvArg);
		BaseClass::AdrModule ()->Lock ();
	}
	
	virtual
	HRESULT
	CIL_STDMETHODCALLTYPE
	QueryInterface
	(REFIID iid, void **ppvInterface)
	CIL_NOTHROW
	{
		return BaseClass::_InternalQueryInterface (iid, ppvInterface);
	}
	
	virtual
	ULONG
	CIL_STDMETHODCALLTYPE
	AddRef
	()
	CIL_NOTHROW
	{
		const ULONG n = BaseClass::InternalAddRef ();
		return n;
	}
	
	virtual
	ULONG
	CIL_STDMETHODCALLTYPE
	Release
	()
	CIL_NOTHROW
	{
		const ULONG n = BaseClass::InternalRelease ();
		
		if (! n)
		{
			const ModuleLockHelper guard (BaseClass::AdrModule ());
			
			// [2016-12-29 :x] Trust me, I know what I am doing !
			// [2016-12-30]    The destructor is now virtual.
			//#if defined (__GNUC__)
			//	#pragma GCC diagnostic push
			//	#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
			//#endif
			
			delete this;
			
			//#if defined (__GNUC__)
			//	#pragma GCC diagnostic pop
			//#endif
		}
		
		return n;
	}
	
public:
	static
	HRESULT
	CIL_WINAPI
	CreateInstance
	(CComObject **ppObject)
	CIL_NOTHROW
	{
		CIL_ASSERT (ppObject);
		if (! ppObject)
			return E_POINTER;
		
		CComObject *pObject;
		HRESULT     hrRet;
		for (;;)
		{
			try
			{
				pObject = new CComObject;
			}
			catch (...)
			{
				pObject = 0;
				hrRet   = E_OUTOFMEMORY;
				break;
			}
			
			Private::ResetPtrGuard <CComObject> g1 (&pObject);
			
			pObject->SetVoid (0);
			
			{
				//const Private::InternalFinalConstructGuard <CComObject> g2 (pObject);
				
				hrRet = pObject->_AtlInitialConstruct ();
				if (FAILED (hrRet))
					break;
			}
			
			g1.Release ();
			break; // Unconditionally.
		}
		
		*ppObject = pObject;
		return hrRet;
	}
};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
