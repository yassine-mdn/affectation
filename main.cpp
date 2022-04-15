#include <iostream>
#include <cstring>
#include "Affectation.h"
#include "Output.h"

int main(int argc , char* argv[])
{
	std::string path = " ";
	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i],"-i") == 0)
			path = argv[i+1];
		else if (strcmp(argv[i],"-h") == 0)
			Output::help();
	}
	if (path != " ")
	{
		Matrice m(path);
		Affectation affectation(m);
		affectation.hongrois(m);
	}
	else
		std::cout<<"Error try typing affectation -h for more info"<<std::endl;

	return 0;
}
