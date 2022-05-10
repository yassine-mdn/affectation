//

#include <algorithm>
#include <sstream>
#include <numeric>
#include "Affectation.h"
#include "Output.h"

//
// Created by yassine on 10/04/2022.

/**
 * Constructer avec parametre prend crée un copie de notre atribue matrice_de_base_ de l'object m
 * et le stocke dans matrice_hongroise_ et initialize size_ à la taille de notre matrice
 *
 * @param m reference constante vers un object de type Matrice est utiliser pour crée un copie
 * de notre matrice_de_base_
 *
 * */
Affectation::Affectation(const Matrice& m)
{
	for (auto& item: m.get_matrice_de_base())
	{
		matrice_hongroise_.push_back(item);
	}
	size_ = static_cast<int> (matrice_hongroise_.size());
}

/**
 * methode inline qui retourne l'indice d'un elemnt donner dans un vecteur v
 *
 * @param v const ref ver un vecteur<int>
 * @param item l'entier d'ou on veut connaitre l'indice
 *
 * */
inline int index_of(const std::vector<int>& v, int item)
{
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] == item)
			return i;
	}
	return -1;
}

/**
 * methode inline qui retourne la somme de 2 vecteurs qui est equivalente au nombre de "bar" (chrati)
 *
 * @param cols const ref ver un vecteur<bool> : true signifie que la colone est barré
 * @param rows const ref ver un vecteur<bool> : true signifie que la ligne est barré
 *
 * */
inline int calc_nbr_of_hashes(std::vector<bool> cols, std::vector<bool> rows)
{
	return (std::accumulate(cols.begin(), cols.end(), 0)
		+ std::accumulate(rows.begin(), rows.end(), 0));
}

/**
 * methode qui resould le problème d'affectation utilisant la methode hongroise
 *
 * @param m const ref ver une Matrice est néssaisaire pour afficher la solution
 * */
void Affectation::hongrois(const Matrice& m)
{
	int step{ 0 };

	// Etape 1 & 2 reduction de lignes et colones

	reduction_rows_and_cols(step);
	std::vector<bool> covered_cols(size_, false);    //vecteur de bool a size_ element initializer a false
	std::vector<bool> covered_rows(size_, false);    //vecteur de bool a size_ element initializer a false

	// Etape 3

	bool done = false;
	while (!done)    //tanque on n'est pas fini
	{
		if (step == 3)
		{
			couverture_de_zeros(covered_cols, covered_rows, step);
			Output::hashed_matric_print(matrice_hongroise_, covered_cols, covered_rows);
		}
		else if (step == 4)
		{
			int min = find_min(covered_rows, covered_cols);
			substact_min(covered_cols, covered_rows, min, step);
			std::cout << "";
		}
		else if (step == 5)
		{
			std::vector<int> sol = find_solution();
			Output::print_solution(m, sol);
			done = true;
		}
	}

}

/**
 * combine les etapes 1 & 2 de la methode hongroise et assure que
 * on retrouve au moin un zero dans chaque ligne/col de notre matrice_hongroise_
 *
 * @param step permet de suivre a quel etape de l'algo de hongrois on se trouve
 * 		initalement a '0', et remit a '3' vers la fin de cete fonction
 * */
void Affectation::reduction_rows_and_cols(int& step)
{
	std::vector<bool>
		col_has_zeros(size_, false);    //permet de suivres qel col on deja un zero intialemnt kamlin false
	for (auto& i: matrice_hongroise_)
	{
		auto min_index = std::min_element(i.begin(), i.end());    //permet d'avoir l'adresse de l'element min
		int min = static_cast<int>(*min_index);            //dereference min_indes
		col_has_zeros[(min_index - i.begin())] =
			true;    //on remet l'elemnt avec la meme pos que min dans notre col_has_zeros a true
		for (int j = 0; j < size_; ++j)
		{
			i[j] = i[j] - min;
		}    //soustrait min de tout les elements de la ligne
	}

	for (int i = 0; i < size_; ++i)
	{
		if (!col_has_zeros[i])        //on s'assure que la colone ne contient pas deja un zero
		{
			int min = (*std::min_element(matrice_hongroise_.begin(), matrice_hongroise_.end(), [i](auto& a, auto& b)
			{ return a[i] < b[i]; }))[i];    //retour le min de la colone i a l'aide de lambda qu'on defini
			for (auto& item: matrice_hongroise_)
			{
				item[i] = item[i] - min;
			}    //soustrait min de tout les elements de la colone
		}
	}
	step = 3;        //on passe a l'etape 3
}

/**
 * permet de couvir les ligne et colone qui contienes des zero commencent
 * avec les lignes qui contienes le plus de zero suivit de colones
 *
 * @param coverd_cols const ref ver un vecteur<bool> : true signifie que la colone est barré
 * @param covered_rows const ref ver un vecteur<bool> : true signifie que la ligne est barré
 * @param step permet de suivre a quel etape de l'algo de hongrois on se trouve
 * 		initalement a '3', et est mit a '5' si lenombre de lignes et colone corver est egale a la taille du problème
 * 		si non il prend la valeur '4'
 *
 * */
void Affectation::couverture_de_zeros(std::vector<bool>& covered_cols, std::vector<bool>& covered_rows, int& step)
{
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			if (!covered_rows[j])    //on cherche que les lignes non couverte
				covered_rows[j] = rows_number_of_zeros(j,
					size_ - i,
					covered_cols); //num zero debute a la taille de probleme et devient plus petit apés chaque iteration
		}
		for (int j = 0; j < size_; ++j)
		{
			if (!covered_cols[j])
				covered_cols[j] = cols_number_of_zeros(j,
					size_ - i,
					covered_rows);//num zero debute a la taille de probleme et devient plus petit apés chaque iteration
		}
	}
	int nbr_of_hashes = calc_nbr_of_hashes(covered_rows, covered_cols);
	if (nbr_of_hashes
		== size_)    //si la valeur de nbr_of_hashes est egale a la taille de probleme on passe directement a létape finale
		step = 5;
	else    //sinon on cherche a reduire encore notre matrice
		step = 4;
}

/**
 * permet de retouver l'a valeur miniumum non couvete
 *
 * @param coverd_cols const ref ver un vecteur<bool> : true signifie que la colone est barré
 * @param covered_rows const ref ver un vecteur<bool> : true signifie que la ligne est barré
 *
 * @return la valeur min retrouver
 *
 * */
int Affectation::find_min(std::vector<bool>& covered_rows, std::vector<bool>& covered_cols)
{
	int min{ INT16_MAX };	//min est initalizez a la valeur max que peut prendre un entier
	for (int i = 0; i < size_; ++i)
	{
		if (!covered_rows[i])
		{
			for (int j = 0; j < size_; ++j)
			{
				if (!covered_cols[j])	//si on retrouve un element d'on les indice i et j ne sont pas couvert
				{
					int current_min = matrice_hongroise_[i][j];
					min = current_min < min ? current_min : min;	//min prend le min entre current_min et min
				}
			}
		}
	}
	return min;
}
/**
 * soustrait le min de tous les elemenst nom barré et lajoute au croisemnt des lignes et colones couvert
 *
 * @param coverd_cols const ref ver un vecteur<bool> : true signifie que la colone est barré
 * @param covered_rows const ref ver un vecteur<bool> : true signifie que la ligne est barré
 * @param min la valeur min a soustraire
 * @param step permet de suivre a quel etape de l'algo de hongrois on se trouve
 * 		prend 3 vers la fin de la fonction pour signifier que les covered_cols & covered_rows doit étre recalculer
 *
 **/
void Affectation::substact_min(std::vector<bool>& covered_cols, std::vector<bool>& covered_rows, int min, int& step)
{
	for (int i = 0; i < size_; ++i)
	{

		for (int j = 0; j < size_; ++j)
		{
			if (!covered_cols[j] && !covered_rows[i])
			{
				matrice_hongroise_[i][j] -= min;	//soustraiction des elemnet non couvert
			}
			else if (covered_cols[j] && covered_rows[i])
			{
				matrice_hongroise_[i][j] += min;	//ma 3reftch nktebha en francais
			}
		}

	}
	std::replace(covered_cols.begin(), covered_cols.end(), true ,false);	//reset de covered_cols
	std::replace(covered_rows.begin(), covered_rows.end(), true ,false);	//reset de covered_rows
	step = 3;
}

/**
 * soustrait le min de tous les elemenst nom barré et lajoute au croisemnt des lignes et colones couvert
 *
 * @return un vecteur qui contient l'indice des elements qui compose la solution
 *
 **/
std::vector<int> Affectation::find_solution()
{
	std::vector<int> vect_solution(size_, -1);
	int max_num_de_zeros{ 1 };
	while (max_num_de_zeros < size_ && !solution_found(vect_solution))
	{
		for (int i = 0; i < size_; ++i)
		{
			if (vect_solution[i] == -1)		//si cette ligne n'a pas encore de zero selectioné
			{
				vect_solution[i] = rows_number_of_zeros(i, max_num_de_zeros, vect_solution);
			}
		}
		++max_num_de_zeros;
	}

	return vect_solution;
}

/**
 * permet de selectioner un zero de la ligne choisi suivant plusieur critére de disponinbilité
 *
 * @param row  indice de la ligne en question
 * @param max_num_of_zeros le numero de zero que on cherche a trouver
 * @param vect_solution  notre vecteur solution
 * @return l'indice du zero que on choisi si on peut le trouver si non retourne '-1'
 */
int Affectation::rows_number_of_zeros(int row, int max_num_of_zeros, const std::vector<int>& vect_solution)
{
	int couter{ 0 };
	int index{ -1 };
	for (int i = 0; i < size_; ++i)        //on parcour la ligne [row] de la matrice_hongroise_
	{
		if (matrice_hongroise_[row][i] == 0)    //lorsqu'on trouve notre premier zero
		{
			if (cols_number_of_zeros(i) == 1)        //si c'est le seul zero dans cette colone on retourne son index
				return i;
			bool is_taken
				{ false };                        //is_taken permet de s'asuré que n'importe quel zero q'on trouve aprés n'est pas deja utiliser
			for (int j = 0; j < size_; ++j)
			{
				if (vect_solution.at(j) == i)
				{
					is_taken =
						true;                //si cette colone est deja reserver on continue de parcourir le vecteur
					continue;
				}
			}
			if (!is_taken)
			{
				++couter;
				index = i;
			}

		}

	}
	if (couter
		== max_num_of_zeros)            //cette condition permet d'assurer que on fait la recherche des zero de maniere croissante pour eviter les conflit
		return index;
	else
		return -1;
}
/**
 * Permet de s'assurer que a trouver une solution pour chaque ligne
 *
 * @param vect_solution le vecteur qui contient les indice des element qui compose notre solution
 * @return retourne un true ssi aucun elements de vect_solution est egale a -1
 */
bool Affectation::solution_found(const std::vector<int>& vect_solution)
{
	return std::all_of(vect_solution.begin(), vect_solution.end(), [](int i)
	{ return i != -1; });
}

/**
 * retourne true si on retrouve le nombre de zero que on veut dans la colone de notre choix
 *
 * @param row l'indice de la colone en question
 * @param min_num_of_zeros le nombre min de zeros à trouver
 * @param covered_cols permet de s'avoir si un zero est deja baré(reserver) ou non
 * */
bool Affectation::cols_number_of_zeros(int col, int min_num_of_zeros, std::vector<bool>& covered_rows)
{
	int couter{ 0 };
	for (int i = 0; i < size_; ++i)
	{
		if (matrice_hongroise_[i][col] == 0 && !covered_rows[i])
			++couter;
	}

	return couter == min_num_of_zeros;
}

/**
 * retourne true si on retrouve le nombre de zero que on veut dans la ligne de notre choix
 *
 * @param row l'indice de la ligne en question
 * @param min_num_of_zeros le nombre min de zeros à trouver
 * @param covered_cols permet de s'avoir si un zero est deja baré(reserver) ou non
 * */
bool Affectation::rows_number_of_zeros(int row, int min_num_of_zeros, std::vector<bool>& covered_cols)
{
	int couter{ 0 };
	for (int i = 0; i < size_; ++i)
	{
		if (matrice_hongroise_[row][i] == 0 && !covered_cols[i])
			++couter;
	}

	return couter == min_num_of_zeros;
}

/**
 * calule le nombre de zero que contient une colone
 *
 * @param col l'indice de la colone
 * @return le nombre de zero que contient la colone d'indice col
 */
int Affectation::cols_number_of_zeros(int col)
{
	int couter{ 0 };
	for (int i = 0; i < size_; ++i)
	{
		if (matrice_hongroise_[i][col] == 0)
			++couter;
	}

	return couter;
}


/**
 * Destructeur par default
 */
Affectation::~Affectation()
= default;
