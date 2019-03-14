#ifndef CIL_DEF_HPP
#define CIL_DEF_HPP 1


#include "Windows.hpp"


CIL_NAMESPACE_BEGIN (CIL)


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <typename T>
T *
New_NoExc
()
{
	try
	{
		return new T ();
	}
	catch (...)
	{
		return 0;
	}
}

template <typename T, typename P0>
T *
New_NoExc
(const P0 &p0)
{
	try
	{
		return new T (p0);
	}
	catch (...)
	{
		return 0;
	}
}

template <typename T, typename P0, typename P1>
T *
New_NoExc
(const P0 &p0, const P1 &p1)
{
	try
	{
		return new T (p0, p1);
	}
	catch (...)
	{
		return 0;
	}
}

template <typename T, typename P0, typename P1, typename P2>
T *
New_NoExc
(const P0 &p0, const P1 &p1, const P2 &p2)
{
	try
	{
		return new T (p0, p1, p2);
	}
	catch (...)
	{
		return 0;
	}
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


CIL_NAMESPACE_END


#endif
