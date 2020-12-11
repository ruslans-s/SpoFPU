#include <iostream>

 double Func(long double x, int y)
{
	
	const  double part = 0.05;
	const  double zero = 0;
	
	 double result = 0;

	__asm
	{
	

		fld x; st == y
		fild y
		; fmul y; st == y * x
		FMULP ST(1), ST(0)
		fcom zero
		fwait
		FSTSW AX
		fwait
		test ax, 0100h
		jnz lessThanZero


		;Цикл для уменьшения x*y до 2^63
		FLDPI
		FADD  ST, ST; ST(0) = 2
		FXCH ST(1)
	
		M1 : FPREM1
		FSTSW  AX
		SAHF
		JP   M1

		passCalc:
		fsin; st == sint(st)
		fmul part; st == st * 0.05
		fstp result; result == st
		jmp exit2

		lessThanZero :
		fld x; st0 == x st1 == x * y
		FiSUB y
		FDIVRP ST(1), ST(0)
		fstp result; result == st

		exit2 :
		fwait
	}

	return result;
}

int main()
{
    std::cout << "Hello World!\n";
	 double P;
	 double x;
	std::cout << "x = ";
	std::cin >> x;
	
	int y;
	std::cout << "y = ";
	std::cin >> y;


	if ((x * y)  >= 0) 
	{
		P = 0.05 * sin(x * y);
	}
	else {
		P = (x - y) / (x * y);
	}
	std::cout << "C++: " << P << std::endl;
	P = Func(x, y);
	std::cout << "ASM " << P << std::endl;
}

