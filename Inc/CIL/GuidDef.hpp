#ifndef CIL_GUIDDEF_HPP
#define CIL_GUIDDEF_HPP 1


#include "_Fwd.hpp"


#if defined (_WIN32)
	#include <Windows.h>
#endif


CIL_NAMESPACE_BEGIN (CIL)
CIL_NAMESPACE_BEGIN (Handy)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_WIN32)
	typedef ::GUID GUID;
	//typedef ::IID  IID ;
#else
	typedef struct
	{
		      UInt32 Data1;
		      UInt16 Data2;
		      UInt16 Data3;
		      UInt8  Data4 [8];
	}
	GUID, IID;
#endif


#if ! defined (_WIN32)

	#if defined (__cplusplus)
		typedef const GUID &REFGUID;
	#else
		typedef const GUID *REFGUID;
	#endif
	
	typedef REFGUID REFIID;
	typedef REFGUID REFCLSID;
	
#endif


#if ! defined (_WIN32)

	#if defined (__cplusplus)
	
		inline
		bool
		operator==
		(REFGUID guid1, REFGUID guid2)
		{
			const BYTE *const pb1 = static_cast <const BYTE *> (static_cast <const void *> (&guid1));
			const BYTE *const pb2 = static_cast <const BYTE *> (static_cast <const void *> (&guid2));
			
			for (unsigned i = 0; i < sizeof (guid1); ++i)
				if (pb1 [i] != pb2 [i])
					return false;
			
			return true;
		}
		
		inline
		bool
		operator!=
		(REFGUID guid1, REFGUID guid2)
		{
			return ! (guid1 == guid2);
		}
	
	#endif

#endif


#if 1

	#if defined (__cplusplus)
	
		inline
		bool
		CIL_WINAPI
		InlineIsEqualUnknown (REFGUID guid)
		{
			return
				guid.Data1     == 0x00000000 &&
				guid.Data2     == 0x0000     &&
				guid.Data3     == 0x0000     &&
				guid.Data4 [0] == 0xC0       &&
				guid.Data4 [1] == 0x00       &&
				guid.Data4 [2] == 0x00       &&
				guid.Data4 [3] == 0x00       &&
				guid.Data4 [4] == 0x00       &&
				guid.Data4 [5] == 0x00       &&
				guid.Data4 [6] == 0x00       &&
				guid.Data4 [7] == 0x46;
		}
		
	#endif

#endif




//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (CIL_INITGUID)

	#define CIL_DEFINE_GUID(name, dw, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
		CIL_EXTERN_C const CIL::Handy::GUID name = { dw, w1, w2, { b1, b2, b3, b4, b5, b6, b7 }  }

#else

	#define CIL_DEFINE_GUID(name, dw, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
		CIL_EXTERN_C const CIL::Handy::GUID name

#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END
CIL_NAMESPACE_END


#endif
