#include <iostream>
#include "Matrix.h"

int main()
{
    std::vector<float> vec = {1., 2., 3.};
    std::vector<std::vector<float>> mat = {{0., 1., 2.}, {1., 2., 3.}, {0., -12., 9.}};

    std::vector<float> product = matrix_vector_mult(mat, vec);

    for (int i = 0; i < 3; i++)
    {
        std::cout << product[i] << " ";
    }
}