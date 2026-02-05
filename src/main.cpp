#include <iostream>
#include "Matrix.h"

int main()
{
    std::vector<std::vector<float>> mat = {{0., 1., 2.}, {1., 2., 3.}, {0., -12., 9.}};

    auto product = matrix_matrix_mult(mat, mat);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << product[i][j] << " ";
        }
        std::cout << '\n';
    }
}