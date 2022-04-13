//
// Created by yassine on 02/04/2022.
//

#ifndef DECISIONMAKINGPROJECT__OUTPUT_H_
#define DECISIONMAKINGPROJECT__OUTPUT_H_

#include "Matrice.h"
class Output
{
 public:
	static void help();
	static void pretty_matrix_print(std::vector<std::vector<int>>& m, std::string text = "");
	static void hashed_matric_print(std::vector<std::vector<int>>& m,
		std::vector<bool>& covered_cols,
		std::vector<bool>& covered_rows,
		std::string text = "");
	static void print_solution(const Matrice& m,std::vector<int> sol);
 private:
	static size_t number_of_digits(float n);
	static size_t number_of_digits(std::string n);
};

#endif //DECISIONMAKINGPROJECT__OUTPUT_H_
