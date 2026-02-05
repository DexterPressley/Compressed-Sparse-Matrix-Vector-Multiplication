#include "Matrix.h"
#include <cassert>

std::vector<float> matrix_vector_mult(std::vector<std::vector<float>> matrix, std::vector<float> vector)
{
    assert(matrix[0].size() == vector.size());

    std::vector<float> output{};

    for (unsigned int i = 0; i < matrix.size(); i++)
    {
        float sum = 0;
        for (unsigned int j = 0; j < matrix.size(); j++)
        {
            sum += matrix[i][j] * vector[j];
        }
        output.push_back(sum);
    }
    return output;
}