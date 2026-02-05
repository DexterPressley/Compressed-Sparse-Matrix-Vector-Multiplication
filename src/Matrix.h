#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

std::vector<float> matrix_vector_mult(std::vector<std::vector<float>> matrix, std::vector<float> vector);

std::vector<std::vector<float>> matrix_matrix_mult(std::vector<std::vector<float>> matrix_1, std::vector<std::vector<float>> matrix_2);

#endif