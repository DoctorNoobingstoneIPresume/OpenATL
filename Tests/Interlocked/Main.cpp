#include <CIL/Interlocked.hpp>

#include <iostream>

#include <Windows.h>


int
main
()
{
	using CIL::InterlockedIncrement;
	using CIL::InterlockedDecrement;
	
	std::cout << "Hello, world !\n" << 10 << "\n";
	
	LONG x = 10;
	LONG y = 42;
	{
		y = InterlockedDecrement (&x);
		std::cout << "x " << x << ", y " << y << "...\n";
		x = InterlockedIncrement (&x);
		std::cout << "x " << x << ", y " << y << "...\n\n";
	}
	
	const bool bCorrect = x == 10 && y == 9;
	std::cout << (bCorrect ? "OK" : "Error") << " !\n";
	return bCorrect ? 0 : 1;
}
