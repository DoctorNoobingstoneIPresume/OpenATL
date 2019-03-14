#ifndef CIL_TESTS_OBJECT_BALLOON_HPP
#define CIL_TESTS_OBJECT_BALLOON_HPP 1


#include <CIL/Object.hpp>


namespace Test
{


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CBalloon
	: public CIL::CComObjectRootEx <CIL::CComObjectThreadModel>
{
protected:
	static
	CIL::CModule *
	AdrModule
	()
	{
		return CIL::AdrModule ();
	}

public:
	~CBalloon
	();
	
	CBalloon
	();

public:
	void
	DoSomething
	();
};


} // end namespace


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


#endif
