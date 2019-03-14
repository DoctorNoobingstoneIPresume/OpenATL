//#include "Balloon.hpp"
#include "Game/CBalloon.hpp"

#include <CIL/Object.hpp>
#include <CIL/Base.hpp>

#include <iostream>
#include <exception>


// [2016-10-10]
//namespace CIL
//{
//	namespace
//	{
//		CModule g_module;
//	}
//	
//	CModule *
//	AdrModule
//	()
//	{
//		//static Module s_module;
//		//return &s_module;
//		return &g_module;
//	}
//}
//
CIL::CModule g_module;


CIL_VIS_HIDDEN
CIL::CModule *
CIL::AdrModule
()
{
	return &g_module;
}


int
do_main
()
{
	std::cout << "Hello, world !\n";
	
	// [2016-10-18]
	#if 0
	if (0)
	{
		CIL::CComObject <Test::CBalloon> obj;
		obj.DoSomething ();
	}
	#endif
	
	#if 0
	for (; 0 ; )
	{
		CIL::CComObject <Test::CBalloon> *pObject;
		{
			const CIL::Handy::HRESULT hr = CIL::CComObject <Test::CBalloon>::CreateInstance (&pObject);
			
			std::cout << "Bla, bla !\n";
			
			if (FAILED (hr))
			{
				std::cout << "CreateInstance failed !\n";
				break;
			}
			
			pObject->DoSomething ();
		}
		
		break; // Unconditionally.
	}
	#endif
	
	using namespace CIL::Handy;
	
	if (0)
	{
		CIL::CComObject <Game::CBalloon> obj;
		
		DWORD   z;
		HRESULT hr;
		{
			hr = obj.MixPotions (10, 20, &z);
		}
		
		if (FAILED (hr))
			{ std::cout << "obj.MixPotions failed !\n"; return 1; }
		
		std::cout << "z " << z << "...\n";
	}
	
	for (; 1; )
	{
		CIL::CComPtr <Game::ISphere> spSphere;
		{
			CIL::CComPtr <IUnknown> spUnk;
			{
				CIL::CComObject <Game::CBalloon> *pObject;
				HRESULT                           hr;
				{
					hr = CIL::CComObject <Game::CBalloon>::CreateInstance (&pObject);
				}
				
				if (FAILED (hr))
					{ std::cout << "CreateInstance failed !\n"; break; }
				
				spUnk = pObject;
			}
			
			{
				const HRESULT hr = spUnk->QueryInterface (Game::IID_ISphere, spSphere.AdrPtrToVoid ());
				if (FAILED (hr))
					{ std::cout << "QueryInterface failed !\n"; break; }
			}
		}
		
		{
			DWORD   z  = -1;
			HRESULT hr;
			{
				hr = spSphere->MixPotions (10, 20, &z);
			}
			
			if (FAILED (hr))
				{ std::cout << "MixPotions failed !\n"; break; }
			
			std::cout << "z " << z << "...\n";
		}
		
		break; // Unconditionally.
	}
	
	
	
	return 0;
}

int
main
()
{
	try
	{
		return do_main ();
	}
	catch (const std::exception &e)
	{
		try { std::cout << "Exception: \"" << e.what () << "\" !\n"; } catch (...) {}
		return -1;
	}
	catch (...)
	{
		try { std::cout << "Exception !\n"; }                          catch (...) {}
		return -1;
	}
}

