#include "Balloon.hpp"

#include <iostream>


namespace Test
{


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CBalloon::~CBalloon
()
{
try
{
	const char *const pszTitle = "CBalloon::~CBalloon";
	std::cout << pszTitle << "\n";
}
catch (...)
{}
}


CBalloon::CBalloon
()
{
	const char *const pszTitle = "CBalloon::CBalloon";
	std::cout << pszTitle << "\n";
}


void
CBalloon::DoSomething
()
{
	const char *const pszTitle = "CBalloon::DoSomething";
	std::cout << pszTitle << "\n";
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


} // end namespace
