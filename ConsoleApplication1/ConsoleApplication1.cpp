// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

 double Func(long double x, int y)
{
	//constants for "__asm" brackets
	const  double part = 0.05;
	const  double zero = 0;
	 double result = 0;

	__asm
	{
	

		fld x; st == y
		fild y
		; fmul y; st == y * x
		FMULP ST(1),ST(0)
		fcom zero
		test ax, 0100h
		fwait
		jnz lessThanZero

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

	if (x * y > (pow(2, 63))) {
		std::cout << "Ошибка, x*y > 2^63" << std::endl;
		return 0;
	}

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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 


//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
