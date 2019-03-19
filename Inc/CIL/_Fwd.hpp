#ifndef CIL__FWD_HPP
#define CIL__FWD_HPP 1


#if 1
	#include <stddef.h>
	#include <stdio.h>
	
	// [2016-11-07] Required for abort:
	#include <stdlib.h>
#endif


#if defined (__DMC__)
	// [2016-12-08]
	//   We have to include <iostream> (or some part of it) before <Windows.h>.
	//   Otherwise, horrible error messages will be thrown at us.
	#include <iostream>
	#include <Windows.h> // Yup, at this point, before we define BYTE, WORD, DWORD, etc.
#endif


#if defined (__cplusplus)
	#if defined (__BORLANDC__)
		typedef size_t    uintptr_t;
		typedef ptrdiff_t  intptr_t;
	#endif
	
	#include <boost/cstdint.hpp>
#else
	#include <stdint.h>
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-10-10]
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_NDEBUG)
	#define CIL_DEBUG 0
#else
	#define CIL_DEBUG 1
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-10-19] TODO:
//   Is this safe ?
//   CIL_INT32_MAX is used where "modern" versions of ATL use LONG_MAX...
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define CIL_INT32_MAX ((int32_t) 0x7FFFFFFF)
#define CIL_INT32_MIN ((int32_t) 0x80000000)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (__cplusplus)
	#define CIL_NAMESPACE_BEGIN(x) namespace x {
	#define CIL_NAMESPACE_END      }
#else
	#define CIL_NAMESPACE_BEGIN(x)
	#define CIL_NAMESPACE_END
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-08-16]
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (__cplusplus)

	namespace CIL
	{
		namespace Handy
		{
		}
		
		using namespace Handy;
	}

#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CIL stands for "COM Is Love", of course.
// This is an example string used somewhere
// (I think that in the Tip-of-the-Day sample application)
// in the wonderful "Inside ATL" book.
// 
// Lots of thanks to Igor Pavlov, the author of LZMA.
// Thanks to him, I was able learn many years ago
// that one can implement COM (or at least an important part of COM)
// even without Windows.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (__cplusplus)
	namespace Handy
	{
		using boost::uint8_t; using boost::uint16_t; using boost::uint32_t; using boost::uint64_t;
		using boost:: int8_t; using boost:: int16_t; using boost:: int32_t; using boost:: int64_t;
		
		#if defined (__BORLANDC__)
			typedef size_t    uintptr_t;
			typedef ptrdiff_t  intptr_t;
		#else
			using boost::uintptr_t;
			using boost:: intptr_t;
		#endif
	}
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2017-01-06]
//   The following are useful for self-documenting code.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (__cplusplus)
	namespace Handy
	{
		typedef uint8_t  size8_t;
		typedef uint16_t size16_t;
		typedef uint32_t size32_t;
		typedef uint64_t size64_t;
	}
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (__cplusplus)

	#define CIL_EXTERN_C       extern "C"
	#define CIL_EXTERN_C_BEGIN extern "C" {
	#define CIL_EXTERN_C_END   }

#else

	#define CIL_EXTERN_C       extern
	#define CIL_EXTERN_C_BEGIN
	#define CIL_EXTERN_C_END

#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-10-10]
//   https://gcc.gnu.org/wiki/Visibility
//   This stuff is useful for AdrModule.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (__GNUC__) && ! defined (__CYGWIN__)

	#define CIL_VIS_DEFAULT __attribute ((visibility ("default")))
	#define CIL_VIS_HIDDEN  __attribute ((visibility ("hidden" )))

#elif defined (CIL_BUILDING)

	#define CIL_VIS_DEFAULT __declspec (dllexport)
	#define CIL_VIS_HIDDEN

#else

	#define CIL_VIS_DEFAULT __declspec (dllimport)
	#define CIL_VIS_HIDDEN

#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CIL_NAMESPACE_BEGIN (Handy)

	#if ! defined (_WIN32)
	
		#if 1
			typedef unsigned char  Byte;
			typedef unsigned char  UInt8;
			typedef signed   char  Int8;
		#endif
		
		#if 1
			typedef unsigned short UInt16;
			typedef          short Int16;
		#endif
		
		#if 0
			typedef unsigned long  UInt32;
			typedef          long  Int32;
		#else
			typedef unsigned int   UInt32;
			typedef          int   Int32;
		#endif
		
		#if 1
			typedef uint64_t       UInt64;
			typedef int64_t        Int64;
		#endif
		
		#if 1
			typedef uintptr_t      UIntPtr;
			typedef intptr_t       IntPtr;
		#endif
		
		#if 1
			typedef size_t         SizeT;
			typedef ptrdiff_t      PtrDiffT;
		#endif
		
		#if 1
			typedef UInt8          BYTE;
			typedef UInt16         WORD;
			typedef UInt32         DWORD;
			typedef UInt64         QWORD;
			
			typedef Int8           SBYTE;
			typedef Int16          SWORD;
			typedef Int32          SDWORD;
			typedef Int64          SQWORD;
		#endif
	
	#endif

CIL_NAMESPACE_END


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_WIN32)
	#define CIL_STDCALL __stdcall
	#define CIL_CDECL   __cdecl
	#define CIL_WINAPI  __stdcall
	#define CIL_OLEAPI  __stdcall
	#define CIL_STDAPI  __stdcall
#else
	#define CIL_STDCALL
	#define CIL_CDECL
	#define CIL_WINAPI
	#define CIL_OLEAPI
	#define CIL_STDAPI
#endif


#if 1
	#define CIL_NOTHROW
#else
	#define CIL_NOTHROW throw ()
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_WIN32)
	#define CIL_CHAR_PATH_SEPARATOR     '\\'
	#define CIL_WCHAR_PATH_SEPARATOR    L'\\'
	#define CIL_STRING_PATH_SEPARATOR   "\\"
	#define CIL_WSTRING_PATH_SEPARATOR  L"\\"
#else
	#define CIL_CHAR_PATH_SEPARATOR     '/'
	#define CIL_WCHAR_PATH_SEPARATOR    L'/'
	#define CIL_STRING_PATH_SEPARATOR   "/"
	#define CIL_WSTRING_PATH_SEPARATOR  L"/"
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if 1
	#define CIL_IN                    
	#define CIL_OUT
	#define CIL_INOUT
	#define CIL_OPT
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// ...
// 
// [2016-09-07] TODO: ...
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if ! CIL_DEBUG
	#define CIL_ASSERT(condition)
#else
	#define CIL_ASSERT(condition) do { if (! (condition)) { printf ("CIL_ASSERT failed: \"%s\" (source file \"%s\":%u).", #condition, __FILE__, __LINE__); abort (); } } while (0)
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// [2016-12-27 :x]
//   ATL uses ATLASSERT, not ATL_ASSERT.
//   For consistency, we also define CILASSERT (in addition to CIL_ASSERT).
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define CILASSERT CIL_ASSERT


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define CIL_TRY_BEGIN                     try {
#define CIL_TRY_END                       }

#define CIL_CATCH_ALL_BEGIN               catch (...) {
#define CIL_CATCH_ALL_END                 }
#define CIL_CATCH_ALL_NOP                 catch (...) {}
#define CIL_CATCH_ALL_RETURN              catch (...) { return; }
#define CIL_CATCH_ALL_RETURN_VALUE(value) catch (...) { return (value); }

#define CIL_TRY_CATCH_ALL_NOP(instr)      do try { instr } catch (...) {} while (0)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef CIL_PACKING
 #define CIL_PACKING 8
#endif

#define CIL_OFFSETOFCLASS(Base, Derived) (reinterpret_cast <std::size_t> (static_cast <Base *> (reinterpret_cast <Derived *> (CIL_PACKING))) - CIL_PACKING)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define CIL_NEW(x)                        new (x)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
