#include <iostream>
#include "Treap.h"
int main()
{
	std::cout << "hi, cursova!" << endl;
	
	Treap T;
	
	for (int i = 0; i < 20; i += 2)
	{
		T.Insert(i);
	}
	T.print();
	system("pause");


	return 0;
}