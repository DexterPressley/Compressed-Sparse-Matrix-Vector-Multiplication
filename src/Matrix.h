#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "types.h"

std::vector<double> matrix_vector_mult(matrix matrix, std::vector<double> vector);

matrix matrix_matrix_mult(matrix matrix_1, matrix matrix_2);

#endif