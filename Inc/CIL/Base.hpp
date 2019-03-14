#ifndef CIL_BASE_HPP
#define CIL_BASE_HPP 1


#include "Windows.hpp"


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CComPtr:
// 
// [2016-06-24]
//   A better name for _NoAddRefReleaseOnCComPtr is _NoAddRefReleaseOnInterface.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class T>
class _NoAddRefReleaseOnInterface
	: public T
{
protected:
	~_NoAddRefReleaseOnInterface
	()
	{}
	
private:
	CIL_STDMETHOD_ (ULONG, AddRef)
	()
	CIL_PURE;
	
	CIL_STDMETHOD_ (ULONG, Release)
	()
	CIL_PURE;
};


template <class T>
class CComPtr
{
public:
	typedef T _PtrClass;
	typedef T value_type;
	
private:
	T *_p;
	
// <SafeBoolIdiom_Part1>
private:
	void
	NoCmpPlease
	()
	const;
	
public:
	typedef
	void
	(CComPtr::*UnspecifiedBoolType)
	()
	const;
	
	operator UnspecifiedBoolType
	()
	const
	{
		return _p ? &CComPtr::NoCmpPlease : 0;
	}
// </SafeBoolIdiom_Part1>
	
public:
	~CComPtr
	()
	{
		if (_p)
			_p->Release ();
	}
	
	void
	Swap
	(CComPtr &rhs)
	{
		T *const pTmp   = _p;
		         _p     = rhs._p;
		         rhs._p = pTmp;
	}
	
	CComPtr
	(const CComPtr &rhs)
		: _p (rhs._p)
	{
		if (_p)
			_p->AddRef ();
	}
	
	CComPtr &
	operator=
	(const CComPtr &rhs)
	{
		CComPtr tmp (rhs);
		Swap (tmp);
		return *this;
	}
	
	CComPtr
	(T *p)
		: _p (p)
	{
		if (_p)
			_p->AddRef ();
	}
	
	CComPtr &
	operator=
	(T *p)
	{
		CComPtr tmp (p);
		Swap (tmp);
		return *this;
	}
	
	CComPtr
	()
		: _p (0)
	{}
	
	// [2016-06-24]
	//   The name "Release" usually means something else for a programmer not accustomed to CComPtr.
	//   Such a programmer would prefer to call this function Reset.
	//   We disable this function for now.
	//   Instead of "sp.Release ();", one can use "sp = 0;".
	//void
	//Release
	//()
	//{
	//	if (IUnknown *const punk = _p)
	//	{
	//		_p = 0;
	//		punk->Release ();
	//	}
	//}
	
	// [2016-06-24]
	//   Please search for SafeBoolIdiom above and below.
	//operator T *
	//()
	//const
	//{
	//	return _p;
	//}
	//
	T *
	Get
	()
	const
	{
		return _p;
	}
	
	T &
	operator*
	()
	const
	{
		CIL_ASSERT (_p);
		return *_p;
	}
	
	_NoAddRefReleaseOnInterface <T> *
	operator->
	()
	const
	{
		CIL_ASSERT (_p);
		return static_cast <_NoAddRefReleaseOnInterface <T> *> (_p);
	}
	
	T **
	AdrPtr
	()
	{
		CIL_ASSERT (! _p);
		return &_p;
	}
	
	// [2016-12-27 :x]
	//   This function is very useful when this pointer is used to store the result of QueryInterface.
	void **
	AdrPtrToVoid
	()
	{
		// [2016-12-29 :x] GCC (probably rightfully) complains: "error: lvalue required as unary '&' operand".
		//return &static_cast <void *> (_p);
		return static_cast <void **> (static_cast <void *> (&_p));
	}
	
	T **
	operator&
	()
	{
		return AdrPtr ();
	}
	
	// [2016-06-24]
	//   More flexible comparison operators are provided below, as non-members.
	//   But please, also see IsEqualObject below.
	//bool
	//operator==
	//(const CComPtr &rhs)
	//const
	//{
	//	return _p == rhs._p;
	//}
	//
	//bool
	//operator<
	//(const CComPtr &rhs)
	//const
	//{
	//	return _p < rhs._p;
	//}
	//
	//bool
	//operator==
	//(T *rhs)
	//const
	//{
	//	return _p == rhs;
	//}
	//
	//bool
	//operator<
	//(T *rhs)
	//const
	//{
	//	return _p < rhs;
	//}
	
	bool
	IsEqualObject
	(IUnknown *rhs)
	{
		if (! _p && ! rhs)
			return true;
		else
		if (! _p || ! rhs)
			return false;
		else
		{
			// [2016-12-27 :x]
			//CComPtr <IUnknown> punk1; { _p ->QueryInterface (IID_IUnknown, &static_cast <void *> (punk1.AdrPtr       ())); }
			CComPtr <IUnknown> punk1; { _p ->QueryInterface (IID_IUnknown,                        punk1.AdrPtrToVoid () ); }
			
			// [2016-12-27 :x]
			//CComPtr <IUnknown> punk2; { rhs->QueryInterface (IID_IUnknown, &static_cast <void *> (punk2.AdrPtr       ())); }
			CComPtr <IUnknown> punk2; { rhs->QueryInterface (IID_IUnknown,                        punk2.AdrPtrToVoid () ); }
			
			return punk1 == punk2;
		}
	}
	
	void
	Attach
	(T *p)
	{
		if (_p)
			_p->Release ();
		
		_p = p;
	}
	
	T *
	Detach
	()
	{
		T *const pRet = _p;
		_p = 0;
		return pRet;
	}
	
	HRESULT
	CopyTo
	(T **pp)
	{
		CIL_ASSERT (pp);
		if (! pp)
			return E_POINTER;
		
		if (_p)
			_p->AddRef ();
		
		if (true)
			*pp = _p;
		
		return S_OK;
	}
};


// <SafeBoolIdiom_Part2>
// [2016-06-24]
//   Actually, we allow comparisons between CComPtr's.
//
//template <typename T, typename U>
//bool
//operator==
//(const CComPtr <T> &lhs, const U &rhs)
//{
//	lhs.NoCmpPlease ();
//	return false;
//}
//
////template <typename T, typename U>
//bool
//operator!=
//(const CComPtr <T> &lhs, const U &rhs)
//{
//	return ! (lhs == rhs);
//}
//
//template <typename T, typename U>
//bool
//operator==
//(const U &lhs, const CComPtr <T> &lhs)
//{
//	rhs.NoCmpPlease ();
//	return false;
//}
//
//template <typename T, typename U>
//bool
//operator!=
//(const U &lhs, const CComPtr <T> &rhs)
//{
//	return ! (lhs == rhs);
//}
//
// </SafeBoolIdiom_Part2>


template <class T, class U> bool operator== (const CComPtr <T> &lhs, const CComPtr <U> &rhs) { return lhs.Get () == rhs.Get (); }
template <class T, class U> bool operator!= (const CComPtr <T> &lhs, const CComPtr <U> &rhs) { return ! (lhs == rhs); }
template <class T, class U> bool operator<  (const CComPtr <T> &lhs, const CComPtr <U> &rhs) { return lhs.Get () <  rhs.Get (); }
template <class T, class U> bool operator>= (const CComPtr <T> &lhs, const CComPtr <U> &rhs) { return ! (lhs <  rhs); }
template <class T, class U> bool operator>  (const CComPtr <T> &lhs, const CComPtr <U> &rhs) { return    rhs <  lhs ; }
template <class T, class U> bool operator<= (const CComPtr <T> &lhs, const CComPtr <U> &rhs) { return ! (lhs >  rhs); }

template <class T, class U> bool operator== (const CComPtr <T> &lhs,                U  *rhs) { return lhs.Get () == rhs; };
template <class T, class U> bool operator!= (const CComPtr <T> &lhs,                U  *rhs) { return ! (lhs == rhs); }
template <class T, class U> bool operator<  (const CComPtr <T> &lhs,                U  *rhs) { return lhs.Get () <  rhs; };
template <class T, class U> bool operator>= (const CComPtr <T> &lhs,                U  *rhs) { return ! (lhs <  rhs); }
template <class T, class U> bool operator>  (const CComPtr <T> &lhs,                U  *rhs) { return    rhs <  lhs ; }
template <class T, class U> bool operator<= (const CComPtr <T> &lhs,                U  *rhs) { return ! (lhs >  rhs); }

template <class T, class U> bool operator== (               T  *lhs, const CComPtr <U> &rhs) { return lhs == rhs.Get (); }
template <class T, class U> bool operator!= (               T  *lhs, const CComPtr <U> &rhs) { return ! (lhs == rhs); }
template <class T, class U> bool operator<  (               T  *lhs, const CComPtr <U> &rhs) { return lhs <  rhs.Get (); }
template <class T, class U> bool operator>= (               T  *lhs, const CComPtr <U> &rhs) { return ! (lhs <  rhs); }
template <class T, class U> bool operator>  (               T  *lhs, const CComPtr <U> &rhs) { return    rhs <  lhs ; }
template <class T, class U> bool operator<= (               T  *lhs, const CComPtr <U> &rhs) { return ! (lhs >  rhs); }


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
