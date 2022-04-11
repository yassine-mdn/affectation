#include <iostream>
#include "Affectation.h"

int main()
{
	Matrice m("test.csv");
	Affectation affectation(m);
	affectation.hongrois();
	return 0;
}
