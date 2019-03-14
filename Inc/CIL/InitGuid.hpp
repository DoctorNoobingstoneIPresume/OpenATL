#ifndef CIL_INITGUID
#define CIL_INITGUID 1


#include "GuidDef.hpp"


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#if defined (_WIN32)
	#if defined (UNDER_CE)
		#include <basetyps.h>
	#endif
	
	#include <initguid.h>
	
	#if defined (UNDER_CE)
		CIL_DEFINE_GUID (IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
	#endif
#else
	//#if 1
	//	CIL_DEFINE_GUID (IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
	//#endif
#endif


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
