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

	explicit Matrice(const std::string& path);
	virtual ~Matrice();
	[[nodiscard]] const std::vector<std::vector<int>>& get_matrice_de_base() const;
	[[nodiscard]] const std::vector<std::string>& get_col_names() const;
	[[nodiscard]] const std::vector<std::string>& get_row_names() const;
 private:
	std::vector<std::vector<int>> matrice_de_base_;
	std::vector<std::string> col_names_;
	std::vector<std::string> row_names_;

};

#endif //DECISIONMAKINGPROJECT__MATRICE_H_
