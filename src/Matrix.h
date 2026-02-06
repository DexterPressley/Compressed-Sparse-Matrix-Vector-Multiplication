#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

std::vector<double> matrix_vector_mult(std::vector<std::vector<double>> matrix, std::vector<double> vector);

std::vector<std::vector<double>> matrix_matrix_mult(std::vector<std::vector<double>> matrix_1, std::vector<std::vector<double>> matrix_2);

#endif