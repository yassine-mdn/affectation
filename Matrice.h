//
// Created by yassine on 02/04/2022.
//

#ifndef DECISIONMAKINGPROJECT__MATRICE_H_
#define DECISIONMAKINGPROJECT__MATRICE_H_

#include <iostream>
#include <vector>
#include <string>

class Matrice
{
 public:

	Matrice(const std::string& path);
	virtual ~Matrice();
	const std::vector<std::vector<int>>& get_matrice_de_base() const;
	void print_matrice();
	const std::vector<std::string>& get_col_names() const;
	const std::vector<std::string>& get_row_names() const;
 private:
	std::vector<std::vector<int>> matrice_de_base_;
	std::vector<std::string> col_names_;
	std::vector<std::string> row_names_;

};

#endif //DECISIONMAKINGPROJECT__MATRICE_H_
