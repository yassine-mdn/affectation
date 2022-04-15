//

#include <algorithm>
#include <sstream>
#include <numeric>
#include "Affectation.h"
#include "Output.h"

//
// Created by yassine on 10/04/2022.
Affectation::Affectation(const Matrice& m)
{
	for (auto& item: m.get_matrice_de_base())
	{
		matrice_hongroise_.push_back(item);
	}
	size = static_cast<int> (matrice_hongroise_.size());
}

inline int index_of(const std::vector<int>& v, int item)
{
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] == item)
			return i;
	}
	return -1;
}

inline int calc_nbr_of_hashes(std::vector<bool> cols, std::vector<bool> rows)
{
	return (std::accumulate(cols.begin(), cols.end(), 0)
		+ std::accumulate(rows.begin(), rows.end(), 0));
}

void Affectation::hongrois(const Matrice& m)
{
	int step{ 0 };

	// Etape 1 & 2

	reduction_rows_and_cols(step);
	std::vector<bool> covered_cols(size, false);
	std::vector<bool> covered_rows(size, false);

	// Etape 3

	bool done = false;
	while (!done)
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

void Affectation::reduction_rows_and_cols(int& step)
{
	std::vector<bool> col_has_zeros(size, false);
	for (auto& i: matrice_hongroise_)
	{
		auto min_index = std::min_element(i.begin(), i.end());
		int min = static_cast<int>(*min_index);
		col_has_zeros[(min_index - i.begin())] = true;
		for (int j = 0; j < size; ++j)
		{
			i[j] = i[j] - min;
		}
	}

	for (int i = 0; i < size; ++i)
	{
		if (!col_has_zeros[i])
		{
			int min = (*std::min_element(matrice_hongroise_.begin(), matrice_hongroise_.end(), [i](auto& a, auto& b)
			{ return a[i] < b[i]; }))[i];
			for (auto& item: matrice_hongroise_)
			{
				item[i] = item[i] - min;
			}
		}
	}
	step = 3;
}

void Affectation::couverture_de_zeros(std::vector<bool>& covered_cols, std::vector<bool>& covered_rows, int& step)
{
	int nbr_of_hashes{ 0 };
	for (int i = 0; i < size; ++i)
	{
		nbr_of_hashes = calc_nbr_of_hashes(covered_rows, covered_cols);
		for (int j = 0; j < size; ++j)
		{
			if (!covered_rows[j] && nbr_of_hashes != size)
				covered_rows[j] = rows_number_of_zeros(j, size - i, covered_cols);
		}
		nbr_of_hashes = calc_nbr_of_hashes(covered_rows, covered_cols);
		for (int j = 0; j < size; ++j)
		{
			if (!covered_cols[j] && nbr_of_hashes != size)
				covered_cols[j] = cols_number_of_zeros(j, size - i, covered_rows);
		}
	}
	nbr_of_hashes = calc_nbr_of_hashes(covered_rows, covered_cols);
	if (nbr_of_hashes == size)
		step = 5;
	else
		step = 4;
}
int Affectation::find_min(std::vector<bool>& covered_rows, std::vector<bool>& covered_cols)
{
	int min{ INT16_MAX };
	for (int i = 0; i < size; ++i)
	{
		if (!covered_rows[i])
		{
			for (int j = 0; j < size; ++j)
			{
				if (!covered_cols[j])
				{
					int current_min = matrice_hongroise_[i][j];
					min = current_min < min ? current_min : min;
				}
			}
		}
	}
	return min;
}

void Affectation::substact_min(std::vector<bool>& covered_cols, std::vector<bool>& covered_rows, int min, int& step)
{
	for (int i = 0; i < size; ++i)
	{

		for (int j = 0; j < size; ++j)
		{
			if (!covered_cols[j] && !covered_rows[i])
			{
				matrice_hongroise_[i][j] -= min;
			}
			else if (covered_cols[j] && covered_rows[i])
			{
				matrice_hongroise_[i][j] += min;
			}
		}

	}
	step = 3;
}

std::vector<int> Affectation::find_solution()
{
	std::vector<int> vect_solution(size, -1);
	int max_num_de_zeros{ 1 };
	while (!solution_found(vect_solution) || max_num_de_zeros < size)
	{
		for (int i = 0; i < size; ++i)
		{
			if (vect_solution[i] == -1)
			{
				vect_solution[i] = rows_number_of_zeros(i, max_num_de_zeros, vect_solution);
			}
		}
		++max_num_de_zeros;
	}

	return vect_solution;
}

bool Affectation::cols_number_of_zeros(int col, int min_num_of_zeros, std::vector<bool>& covered_rows)
{
	int couter{ 0 };
	for (int i = 0; i < size; ++i)
	{
		if (matrice_hongroise_[i][col] == 0 && !covered_rows[i])
			++couter;
	}

	return couter == min_num_of_zeros;
}
bool Affectation::rows_number_of_zeros(int row, int min_num_of_zeros, std::vector<bool>& covered_cols)
{
	int couter{ 0 };
	for (int i = 0; i < size; ++i)
	{
		if (matrice_hongroise_[row][i] == 0 && !covered_cols[i])
			++couter;
	}

	return couter == min_num_of_zeros;
}

int Affectation::cols_number_of_zeros(int col)
{
	int couter{ 0 };
	for (int i = 0; i < size; ++i)
	{
		if (matrice_hongroise_[i][col] == 0)
			++couter;
	}

	return couter;
}

int Affectation::rows_number_of_zeros(int row, int max_num_of_zeros, const std::vector<int>& vect_solution)
{
	int couter{ 0 };
	int index{ -1 };
	for (int i = 0; i < size; ++i)		//on parcour la ligne [row] de la matrice_hongroise_
	{
		if (matrice_hongroise_[row][i] == 0)	//lorsqu'on trouve notre premier zero
		{
			if (cols_number_of_zeros(i) == 1)		//si c'est le seul zero dans cette colone on retourne son index
				return i;
			bool is_taken{ false };						//is_taken permet de s'asuré que n'importe quel zero q'on trouve aprés n'est pas deja utiliser
			for (int j = 0; j < size; ++j)
			{
				if (vect_solution.at(j) == i)
				{
					is_taken = true;				//si cette colone est deja reserver on continue de parcourir le vecteur
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
	if (couter == max_num_of_zeros)			//cette condition permet d'assurer que on fait la recherche des zero de maniere croissante pour eviter les conflit
		return index;
	else
		return -1;
}

bool Affectation::solution_found(const std::vector<int>& vect_solution)
{
	return std::all_of(vect_solution.begin(), vect_solution.end(), [](int i)
	{ return i != -1; });
}

Affectation::~Affectation()
= default;
