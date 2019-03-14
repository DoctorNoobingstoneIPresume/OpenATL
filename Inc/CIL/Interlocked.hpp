#ifndef CIL_INTERLOCKED_HPP
#define CIL_INTERLOCKED_HPP 1


#include "Windows.hpp"


#if defined (_WIN32)
	#include <Windows.h>
#elif defined (__GNUC__)
	#include <ext/atomicity.h>
#else
	#error Unsupported toolset !

#endif


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

typedef int32_t  AtomicInt;
typedef uint32_t AtomicUInt;


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_WIN32)

	// [2016-12-08]
	//inline
	//LONG
	//InterlockedIncrement
	//(volatile LONG *px)
	//{
	//	return ::InterlockedIncrement (px);
	//}
	//
	using ::InterlockedIncrement;
	
	template <typename T>
	inline
	T
	InterlockedIncrement
	(volatile T *px)
	{
		typedef char SizeCheck [sizeof (*px) == sizeof (LONG) ? 1 : -1];
		
		volatile LONG *const py = static_cast <volatile LONG *> (static_cast <volatile void *> (px));
		
		return T (InterlockedIncrement (py));
	}
	
	// [2016-12-08]
	//inline
	//LONG
	//InterlockedDecrement
	//(volatile LONG *px)
	//{
	//	return ::InterlockedDecrement (px);
	//}
	//
	using ::InterlockedDecrement;
	
	template <typename T>
	inline
	T
	InterlockedDecrement
	(volatile T *px)
	{
		typedef char SizeCheck [sizeof (*px) == sizeof (LONG) ? 1 : -1];
		
		volatile LONG *const py = static_cast <volatile LONG *> (static cast <volatile void *> (px));
		
		return T (InterlockedDecrement (py));
	}

#elif defined (__GNUC__)

	static
	inline
	_Atomic_word
	InterlockedIncrement
	(volatile _Atomic_word *px)
	{
		return __gnu_cxx::__exchange_and_add_dispatch (const_cast <_Atomic_word *> (px), +1) + 1;
	}
	
	template <typename T>
	static
	inline
	T
	InterlockedIncrement
	(volatile T *px)
	{
		typedef char SizeCheck [sizeof (*px) == sizeof (_Atomic_word) ? 1 : -1] __attribute__ ((unused));
		
		volatile _Atomic_word *const py = static_cast <volatile _Atomic_word *> (static_cast <volatile void *> (px));
		
		return T (InterlockedIncrement (py));
	}
	
	static
	inline
	_Atomic_word
	InterlockedDecrement
	(volatile _Atomic_word *px)
	{
		return __gnu_cxx::__exchange_and_add_dispatch (const_cast <_Atomic_word *> (px), -1) - 1;
	}
	
	template <typename T>
	static
	inline
	T
	InterlockedDecrement
	(volatile T *px)
	{
		typedef char SizeCheck [sizeof (*px) == sizeof (_Atomic_word) ? 1 : -1] __attribute__ ((unused));
		
		volatile _Atomic_word *const py = static_cast <volatile _Atomic_word *> (static_cast <volatile void *> (px));
		
		return T (InterlockedDecrement (py));
	}

#else

	#error Unsupported toolset !

#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
