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

std::vector<std::vector<float>> matrix_matrix_mult(std::vector<std::vector<float>> matrix_1, std::vector<std::vector<float>> matrix_2)
{
    assert(matrix_1[0].size() == matrix_2.size());

    std::vector<std::vector<float>> output{};

    for (unsigned int i = 0; i < matrix_1.size(); i++)
    {
        std::vector<float> row{};
        for (unsigned int j = 0; j < matrix_2[0].size(); j++)
        {
            float sum = 0;
            for (unsigned int k = 0; k < matrix_2.size(); k++)
            {
                sum += matrix_1[i][k] * matrix_2[k][j];
            }
            row.push_back(sum);
        }
        output.push_back(row);
    }
    return output;
}
