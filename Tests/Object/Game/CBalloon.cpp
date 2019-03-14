#include "CBalloon.hpp"


namespace Game
{


//virtual
HRESULT
CIL_STDMETHODCALLTYPE
CBalloon::MixPotions
(DWORD x, DWORD y, DWORD *pz)
{
	if (! pz)
		return E_POINTER;
	
	*pz = x + y;
	return S_OK;
}


} // end namespace
