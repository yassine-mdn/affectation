//
// Created by yassine on 10/04/2022.
//

#ifndef AFFECTATION__AFFECTATION_H_
#define AFFECTATION__AFFECTATION_H_
#include "Matrice.h"

class Affectation
{
 public:
	void hongrois(const Matrice& m);
	explicit Affectation(const Matrice& m);
	virtual ~Affectation();
 private:
	std::vector<std::vector<int>> matrice_hongroise_;
	int size_;
	void reduction_rows_and_cols(int& step);
	void couverture_de_zeros(std::vector<bool>& covered_cols, std::vector<bool>& covered_rows, int& step);
	bool cols_number_of_zeros(int col, int min_num_of_zeros, std::vector<bool>& covered_rows);
	bool rows_number_of_zeros(int row, int min_num_of_zeros, std::vector<bool>& covered_cols);
	int find_min(std::vector<bool>& covered_rows, std::vector<bool>& covered_cols);
	void substact_min(std::vector<bool>& covered_cols, std::vector<bool>& covered_rows, int min, int& step);
	std::vector<int> find_solution();
	int rows_number_of_zeros(int row, int max_num_of_zeros, const std::vector<int>& vect_solution);
	static bool solution_found(const std::vector<int>& vect_solution);
	int cols_number_of_zeros(int col);
};

#endif //AFFECTATION__AFFECTATION_H_
