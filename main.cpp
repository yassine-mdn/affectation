#include <iostream>
#include <unistd.h>
#include "Affectation.h"

int main(int argc , char* argv[])
{
	Matrice m("test.csv");
	Affectation affectation(m);
	affectation.hongrois(m);
	return 0;
}
