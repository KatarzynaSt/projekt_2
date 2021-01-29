#include <iostream>
#include "samochod.h"
using namespace std;

int main()
{
	cout << "Witaj w moim symulatorze jazdy" << endl;

	Samochod S;
	S.jazda();

	cout << "koniec main" << endl;
	system("pause > 0");
}