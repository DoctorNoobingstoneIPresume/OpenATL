#ifndef CIL_TESTS_OBJECT_GAME_ISPHERE_HPP
#define CIL_TESTS_OBJECT_GAME_ISPHERE_HPP 1


#include "_Fwd.hpp"


namespace Game
{


CIL_DEFINE_GUID (IID_ISphere, 0xAAAAAAAA, 0xBBBB, 0xCCCC, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07);

struct ISphere
//CIL_MIDL_INTERFACE ("AAAAAAAA-BBBB-CCCC-0001-0203-04050607") ISphere
	: public IUnknown
{
	virtual
	HRESULT
	CIL_STDMETHODCALLTYPE
	MixPotions
	(DWORD x, DWORD y, DWORD *pz)
	= 0;
};


} // end namespace


#endif
