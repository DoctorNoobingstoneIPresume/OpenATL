#ifndef CIL_TESTS_OBJECT_GAME_CBALLOON_HPP
#define CIL_TESTS_OBJECT_GAME_CBALLOON_HPP 1


#include "ISphere.hpp"

#include <CIL/Object.hpp>


namespace Game
{


class CBalloon
	: public CIL::CComObjectRootEx <CIL::CComMultiThreadModelNoCS>
	, public ISphere
{
public:
	CIL_BEGIN_COM_MAP (CBalloon)
	
		CIL_COM_INTERFACE_ENTRY_IID (IID_ISphere, ISphere)
	
	CIL_END_COM_MAP   ()
	
	
public:
	typedef _ComMapClass T1;
	

public:
	//virtual
	HRESULT
	CIL_STDMETHODCALLTYPE
	MixPotions
	(DWORD x, DWORD y, DWORD *pz);
};


} // end namespace


#endif
