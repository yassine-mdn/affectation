#include <iostream>
#include <cstring>
#include "Affectation.h"
#include "Output.h"

/**
 * Ce programe nous permet de resoudre les problèmes d'affectation
 * il preut prendre 3 CMD args differents Et imprime le resultat dans le terminal
 * */
int main(int argc , char* argv[])
{
	std::string path = " ";		//on initialize la variable path a " "
	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i],"-i") == 0)		// permet de donner a la variable path le non du fichier source
			path = argv[i+1];
		else if (strcmp(argv[i],"-h") == 0)
			Output::help();		//affiche la page help
	}
	if (path != " ")
	{
		Matrice m(path);		//Generation de notre matrice avec un constructeur qui prend le chemin comme param
		Affectation affectation(m);		//Generation de notre objet Affectation a l'aide de la matrice m
		affectation.hongrois(m);		//resolution avec la methode hongrois
	}
	else
		std::cout<<"Error try typing affectation -h for more info"<<std::endl;

	return 0;
}
