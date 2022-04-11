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
	static void pretty_matrix_print(std::vector<std::vector<float>>& m, std::string text ="");
	static void output_matrix_to_file(std::vector<std::vector<float>>& m, std::string path, std::string title ="", std::string text ="");
	static void intialize_file(std::string path);
 private:
	static size_t number_of_digits(float n);
};

#endif //DECISIONMAKINGPROJECT__OUTPUT_H_
