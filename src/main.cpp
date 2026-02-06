#include <iostream>
#include "Matrix.h"
#include "CRS.h"
#include "CCS.h"
#include "SampleMatrix.h"

int main()
{
    std::vector<std::vector<double>> mat = {{0., 1., 2.}, {1., 2., 3.}, {0., -12., 9.}, {3., 2., 7.}};

    auto crs = to_crs(mat);

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

    auto reconstruct_crs = from_crs(crs);

    // for (unsigned int i = 0; i < reconstruct_crs.size(); i++)
    // {
    //     for (unsigned int j = 0; j < reconstruct_crs.size(); j++)
    //     {
    //         std::cout << reconstruct_crs[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }

    auto ccs = to_ccs(mat);

    // std::cout << "val: ";
    // for (unsigned int i = 0; i < ccs.val.size(); i++)
    // {
    //     std::cout << ccs.val[i] << " ";
    // }
    // std::cout << '\n';

    // std::cout << "col_ind: ";
    // for (unsigned int i = 0; i < ccs.row_ind.size(); i++)
    // {
    //     std::cout << ccs.row_ind[i] << " ";
    // }
    // std::cout << '\n';

    // std::cout << "row_ptr: ";
    // for (unsigned int i = 0; i < ccs.col_ptr.size(); i++)
    // {
    //     std::cout << ccs.col_ptr[i] << " ";
    // }
    // std::cout << '\n';

    auto reconstruct_ccs = from_ccs(ccs);

    // for (unsigned int i = 0; i < reconstruct_ccs.size(); i++)
    // {
    //     for (unsigned int j = 0; j < reconstruct_ccs.size(); j++)
    //     {
    //         std::cout << reconstruct_ccs[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }

    std::cout << '\n';

    std::vector<double> test = {
        3.,
        1.,
        2.,
    };

    std::vector<double> matrix_product = matrix_vector_mult(mat, test);

    std::vector<double> crs_product = crs_vector_mult(crs, test);

    std::vector<double> ccs_product = ccs_vector_mult(ccs, test);

    for (unsigned int i = 0; i < matrix_product.size(); i++)
    {
        std::cout << matrix_product[i] << ' ';
    }
    std::cout << '\n';

    for (unsigned int i = 0; i < crs_product.size(); i++)
    {
        std::cout << crs_product[i] << ' ';
    }
    std::cout << '\n';

    for (unsigned int i = 0; i < ccs_product.size(); i++)
    {
        std::cout << ccs_product[i] << ' ';
    }
    std::cout << '\n';
}