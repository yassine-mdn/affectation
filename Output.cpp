//
// Created by yassine on 02/04/2022.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include "Output.h"
#include "ConsoleColor.h"

using namespace std;

void Output::help()
{
	cout << "resolution problem d'affectation\n\n"
			"affectation [-h] [-g] [-i][filename] [-v] [-o][filename] [-W] [-L] [-H][coefficient] [-S] [-M] [-g]\n\n"
			"-h\tShows help page\n"
			"-i\tTakes input file name\n\tall input files should be put in the input folder and be of the csv format\n";
}

void Output::pretty_matrix_print(vector<vector<int>>& m, std::string text)
{
	size_t maxColLen[m.at(0).size()];
	for (int i = 0; i < m.at(0).size(); ++i)
	{
		maxColLen[i] = 0;
	}
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m.at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m[i][j]) };
			if (num_length > maxColLen[j])
				maxColLen[j] = num_length;
		}
	}

	cout << text << endl;

	for (auto& j: m)
	{
		for (int i = 0; i < j.size(); ++i)
		{
			cout << (i == 0 ? "\n| " : "") << setw((int)maxColLen[i]) << j[i] << (i == j.size() - 1 ? " |" : " ");
		}
	}
	cout << "\n";

}

void Output::hashed_matric_print(vector<std::vector<int>>& m,
	vector<bool>& covered_cols,
	vector<bool>& covered_rows,
	std::string text)
{
	size_t maxColLen[m.at(0).size()];
	for (int i = 0; i < m.at(0).size(); ++i)
	{
		maxColLen[i] = 0;
	}
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m.at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m[i][j]) };
			if (num_length > maxColLen[j])
				maxColLen[j] = num_length;
		}
	}

	cout << text << endl;

	for (int j = 0; j < m.size(); ++j)
	{
		for (int i = 0; i < m.size(); ++i)
		{
			if (covered_rows[j] || covered_cols[i])
				cout << (i == 0 ? "\n| " : "") << setw((int)maxColLen[i]) << red << m[j][i] << white
					 << (i == m.size() - 1 ? " |" : " ");
			else
				cout << (i == 0 ? "\n| " : "") << setw((int)maxColLen[i]) << m[j][i]
					 << (i == m.size() - 1 ? " |" : " ");
		}
	}
	cout << "\n";
}

size_t Output::number_of_digits(float n)
{
	ostringstream str;
	str << n;
	return str.str().size();
}
void Output::print_solution(const Matrice& m, std::vector<int> sol)
{
	size_t maxColLen[m.get_matrice_de_base().at(0).size()];

	for (int i = 0; i < m.get_matrice_de_base().size(); ++i)
	{
		maxColLen[i] = number_of_digits(m.get_col_names()[i]);
		for (int j = 0; j < m.get_matrice_de_base().at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m.get_matrice_de_base()[i][j]) };
			if (num_length > maxColLen[j])
				maxColLen[j] = num_length;
		}
	}

	cout << "La solution est:" << endl;

	for (int j = 0; j < m.get_matrice_de_base().size(); ++j)
	{
		if (j == 0)
		{
			for (int i = 0; i < m.get_matrice_de_base().size(); ++i)
			{
				if (i == 0)
					cout << "\n| " << setw((int)maxColLen[i]) << " ";
				cout << " " << setw((int)maxColLen[i]) << red << m.get_col_names()[i]
					 << white << (i == m.get_matrice_de_base().size() - 1 ? " |" : " ");
			}
		}
		for (int i = 0; i < m.get_matrice_de_base().size(); ++i)
		{
			if (i == 0)
				cout << (i == 0 ? "\n| " : "") << setw((int)maxColLen[i]) << red << m.get_row_names()[j]
					 << white;
			if (sol[j] == i)
				cout << " " << setw((int)maxColLen[i]) << yellow << m.get_matrice_de_base()[j][i]
					 << white << (i == m.get_matrice_de_base().size() - 1 ? " |" : " ");
			else
				cout << " " << setw((int)maxColLen[i]) << m.get_matrice_de_base()[j][i]
					 << (i == m.get_matrice_de_base().size() - 1 ? " |" : " ");
		}
	}
	cout << "\n\n";

	for (int i = 0; i < m.get_matrice_de_base().size(); ++i)
	{
		cout << red << m.get_row_names()[i] << white << " -> " << red << m.get_col_names()[sol[i]] << white << " : "<< m.get_matrice_de_base()[i][sol[i]]<<"\n";
	}

	int cout_min{0};
	for (int i = 0; i < m.get_matrice_de_base().size(); ++i)
	{
		cout_min += m.get_matrice_de_base()[i][sol[i]];
	}
	cout<<"\nLe cout min est:"<<yellow<<cout_min<<endl;
}
size_t Output::number_of_digits(std::string n)
{
	ostringstream str;
	str << n;
	return str.str().size();
}



