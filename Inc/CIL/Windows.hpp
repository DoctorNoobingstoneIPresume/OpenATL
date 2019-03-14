#ifndef CIL_WINDOWS_HPP
#define CIL_WINDOWS_HPP 1


#include "GuidDef.hpp"


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if 1

	#if defined (_WIN32)
		#define CIL_STDMETHODCALLTYPE     __stdcall
	#else
		#define CIL_STDMETHODCALLTYPE
	#endif
	
	#if 1
		#define CIL_STDMETHOD_(type, fn)  virtual type    CIL_STDMETHODCALLTYPE fn
		#define CIL_STDMETHOD(fn)         virtual HRESULT CIL_STDMETHODCALLTYPE fn
		#define CIL_STDMETHODIMP_(type)           type    CIL_STDMETHODCALLTYPE
		#define CIL_STDMETHODIMP                  HRESULT CIL_STDMETHODCALLTYPE
	#endif
	
	#if 1
		#define CIL_PURE                  = 0
		
		#define CIL_MIDL_INTERFACE(x)     struct
	#endif
		
#endif
		

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_WIN32)

	// [2016-08-16]
	//   "GuidDef.hpp" now includes <Windows.h>.
	//#include <Windows.h>
	
	CIL_NAMESPACE_BEGIN (CIL)
	CIL_NAMESPACE_BEGIN (Handy)
	
		#if defined (__cplusplus)
		
			// [2016-12-07]
			//typedef unsigned char     UCHAR;
			//typedef          char     CHAR;
			//typedef unsigned char     BYTE;
			//typedef signed   char     SBYTE;
			//
			//typedef unsigned short    USHORT;
			//typedef          short    SHORT;
			//typedef unsigned short    WORD;
			//typedef          short    SWORD;
			//
			//typedef unsigned int      UINT;
			//typedef          int      INT;
			//typedef unsigned long     UINT32;
			//typedef          long     INT32;
			//typedef unsigned long     ULONG;
			//typedef          long     LONG;
			//typedef unsigned long     DWORD;
			//typedef          long     DWORD;
			//
			//typedef          int      BOOL;
			//
			//typedef unsigned __int64  ULONGLONG;
			//typedef          __int64  LONGLONG;
			//
			
			using ::UCHAR;
			using ::CHAR;
			using ::BYTE;
			typedef signed   char     SBYTE;
			
			using ::USHORT;
			using ::SHORT;
			using ::WORD;
			typedef          short    SWORD;
			
			using ::UINT;
			using ::INT;
			using ::UINT32;
			using ::INT32;
			using ::ULONG;
			using ::LONG;
			using ::DWORD;
			typedef          long     SDWORD;
			
			using ::BOOL;
			
			using ::ULONGLONG;
			using ::LONGLONG;
			
			using ::UINT_PTR;
			using ::ULONG_PTR;
			using ::DWORD_PTR;
			using ::INT_PTR;
			using ::LONG_PTR;
			typedef          INT_PTR  SDWORD_PTR;
			
			using ::LARGE_INTEGER;
			using ::ULARGE_INTEGER;
			using ::FILETIME;
			
			using ::HRESULT;
		
		#endif
	
	CIL_NAMESPACE_END
	CIL_NAMESPACE_END
	
#else

	CIL_NAMESPACE_BEGIN (CIL)
	CIL_NAMESPACE_BEGIN (Handy)
	
		#if 1
		
			typedef unsigned char     UCHAR;
			typedef          char     CHAR;
			typedef unsigned char     BYTE;
			typedef signed   char     SBYTE;
			
			typedef unsigned short    USHORT;
			typedef          short    SHORT;
			typedef          UInt16   WORD;
			typedef          Int16    SWORD;
			
			typedef unsigned int      UINT;
			typedef          int      INT;
			typedef          UInt32   UINT32;
			typedef          Int32    INT32;
			typedef          UINT32   ULONG;
			typedef          INT32    LONG;
			typedef          UInt32   DWORD;
			typedef          Int32    SDWORD;
			
			typedef          int      BOOL;
			
			typedef          UInt64   ULONGLONG;
			typedef          Int64    LONGLONG;
			
			typedef          UIntPtr  UINT_PTR, ULONG_PTR, DWORD_PTR;
			typedef          IntPtr   INT_PTR , LONG_PTR , SDWORD_PTR;
			
			
			
			typedef union _LARGE_INTEGER
			{
				struct
				{
					DWORD LowPart;
					LONG  HighPart;
				};
				
				struct
				{
					DWORD LowPart;
					LONG  HighPart;
				} u;
				
				LONGLONG QuadPart;
			} LARGE_INTEGER, *PLARGE_INTEGER;
			
			
			
			typedef union _ULARGE_INTEGER
			{
				struct
				{
					DWORD LowPart;
					DWORD HighPart;
				};
				
				struct
				{
					DWORD LowPart;
					DWORD HighPart;
				} u;
				
				ULONGLONG QuadPart;
			} ULARGE_INTEGER, *PULARGE_INTEGER;
			
			
			
			typedef struct _FILETIME
			{
				DWORD dwLowDateTime;
				DWORD dwHighDateTime;
			} FILETIME;
		
		#endif
		


		#if 1	
			
			typedef LONG HRESULT;
		
		#endif
		
		
		
		#if defined (__cplusplus)
			// [2016-12-05] These are imported in the global namespace eventually.
			inline bool CIL_SUCCEEDED (HRESULT hr) { return hr >= 0; }
			inline bool CIL_FAILED    (HRESULT hr) { return hr <  0; }
			
			inline bool     SUCCEEDED (HRESULT hr) { return CIL_SUCCEEDED (hr); }
			inline bool     FAILED    (HRESULT hr) { return CIL_FAILED    (hr); }
		#else
			#define CIL_SUCCEEDED(hr) ((HRESULT) (hr) >= 0)
			#define CIL_FAILED(hr)    ((HRESULT) (hr) <  0)
			
			#define SUCCEEDED(hr) (CIL_SUCCEEDED (hr))
			#define FAILED(hr)    (CIL_FAILED    (hr))
		#endif
		
		
		
		#if defined (__cplusplus)
			const HRESULT S_OK                           = 0x00000000;
			const HRESULT S_FALSE                        = 0x00000001;
			
			const HRESULT E_INVALIDARG                   = 0x80070057;
			const HRESULT E_ABORT                        = 0x80004004;
			const HRESULT E_ACCESSDENIED                 = 0x80070005;
			const HRESULT E_FAIL                         = 0x80004005;
			const HRESULT E_HANDLE                       = 0x80070006;
			const HRESULT E_NOINTERFACE                  = 0x80004002;
			const HRESULT E_NOTIMPL                      = 0x80004001;
			const HRESULT E_OUTOFMEMORY                  = 0x8007000E;
			const HRESULT E_PENDING                      = 0x8000000A;
			const HRESULT E_POINTER                      = 0x80004003;
			const HRESULT E_UNEXPECTED                   = 0x8000FFFF;
			const HRESULT STG_E_INVALIDFUNCTION          = 0x80030001;
		#else
			#define       S_OK                  ((HRESULT) 0x00000000)
			#define       S_FALSE               ((HRESULT) 0x00000001)
			
			#define       E_INVALIDARG          ((HRESULT) 0x80070057)
			#define       E_ABORT               ((HRESULT) 0x80004004)
			#define       E_ACCESSDENIED        ((HRESULT) 0x80070005)
			#define       E_FAIL                ((HRESULT) 0x80004005)
			#define       E_HANDLE              ((HRESULT) 0x80070006)
			#define       E_NOINTERFACE         ((HRESULT) 0x80004002)
			#define       E_NOTIMPL             ((HRESULT) 0x80004001)
			#define       E_OUTOFMEMORY         ((HRESULT) 0x8007000E)
			#define       E_PENDING             ((HRESULT) 0x8000000A)
			#define       E_POINTER             ((HRESULT) 0x80004003)
			#define       E_UNEXPECTED          ((HRESULT) 0x8000FFFF)
			#define       STG_E_INVALIDFUNCTION ((HRESULT) 0x80030001)
		#endif
		
		
		
		#if defined (__cplusplus)
		
			// [2016-12-29 :x] TODO: Are we going to define IID_IUnknown too many times or too few times ?
			CIL_DEFINE_GUID (IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
			//CIL_EXTERN_C const CIL::Handy::GUID IID_IUnknown;
			
			// [2016-12-29 :x] TODO:
			//   InlineIsEqualUnknown has been relocated to "GuidDef.hpp" ! Is that okay ?
			//   Anyway, thou shalt not change the value of IID_IUnknown !
			
			CIL_MIDL_INTERFACE ("00000000-0000-0000-C000-000000000046")
			IUnknown
			{
				CIL_STDMETHOD_ (HRESULT, QueryInterface)
				(CIL_IN REFIID riid, CIL_OUT void **ppvInterface)
				CIL_PURE;
				
				CIL_STDMETHOD_ (ULONG  , AddRef)
				()
				CIL_PURE;
				
				CIL_STDMETHOD_ (ULONG  , Release)
				()
				CIL_PURE;
			};
			
			typedef IUnknown *LPUNKNOWN;
		
		#endif
	
	CIL_NAMESPACE_END
	CIL_NAMESPACE_END
	
	
	#if defined (__cplusplus)
		// [2016-12-05] I told you these would be imported in the global namespace eventually.
		using CIL::Handy::CIL_SUCCEEDED;
		using CIL::Handy::CIL_FAILED;
		
		
		using CIL::Handy::SUCCEEDED;
		using CIL::Handy::FAILED;
	#endif

#endif



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


#endif
