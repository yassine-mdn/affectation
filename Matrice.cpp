//
// Created by yassine on 02/04/2022.
//

#include "Matrice.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

Matrice::~Matrice()
= default;

Matrice::Matrice(const std::string& path)
{
	std::fstream file;
	std::string fullPath = "Testing/Input/";    //TODO:When in release configuration change input folder
	fullPath.append(path);
	file.open(fullPath, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "file name or path invalid\n";
		return;
	}
	/*the next stipet of code is supposed to convert the raw csv data into our main matrix and col & row names
	 * is_first_row is always true for first line of the csv file
	 * is_first_element is only evaluated to true when accesing the fist element of every line starting from the second one */
	bool is_first_row{ true};
	bool is_first_element{ true};
	while (file)
	{
		std::string line;
		if (!getline(file, line)) break;

		std::istringstream ss(line);
		std::vector<int> rows;

		while (ss)
		{
			std::string s;
			if (!getline(ss, s, ',')) break;
			if (s.compare("") != 0)
			{
				if (is_first_row)
				{ col_names_.push_back(s); }
				else
				{
					if (is_first_element)
						row_names_.push_back(s);
					else
						rows.push_back(std::stoi(s));
				}
			}
			is_first_element = false;
		}
		is_first_element = true;
		if (!is_first_row)
			matrice_de_base_.push_back(rows);
		is_first_row = false;
	}
}

const std::vector<std::vector<int>>& Matrice::get_matrice_de_base() const
{
	return matrice_de_base_;
}
const vector<std::string>& Matrice::get_col_names() const
{
	return col_names_;
}
const vector<std::string>& Matrice::get_row_names() const
{
	return row_names_;
}

