#include <iostream>
#include "Matrix.h"
#include "CRS.h"
#include "SampleMatrix.h"

int main()
{
    std::vector<std::vector<float>> mat = {{0., 1., 2.}, {1., 2., 3.}, {0., -12., 9.}};

    auto crs = to_crs(problem_1);

    std::cout << "val: ";
    for (unsigned int i = 0; i < crs.val.size(); i++)
    {
        std::cout << crs.val[i] << " ";
    }
    std::cout << '\n';

    std::cout << "col_ind: ";
    for (unsigned int i = 0; i < crs.col_ind.size(); i++)
    {
        std::cout << crs.col_ind[i] << " ";
    }
    std::cout << '\n';

    std::cout << "row_ptr: ";
    for (unsigned int i = 0; i < crs.row_ptr.size(); i++)
    {
        std::cout << crs.row_ptr[i] << " ";
    }
    std::cout << '\n';
}