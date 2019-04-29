#include <iostream>
#include <iomanip>

#include "Checkers.h"

using namespace std;

int main()
{
	Checkers checkers;

	checkers.print(20);
	
	while (true)
	{
		int fromRow, fromCol, toRow, toCol;

		cout << "move from: ";
		cin >> fromRow >> fromCol;

		cout << "move to: ";
		cin >> toRow >> toCol;

		checkers.movePeice(fromRow, fromCol, toRow, toCol);

		checkers.print();
	}
	system("pause");
	return 0;
}