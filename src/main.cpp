#include <iostream>
#include <cassert>
#include "Matrix.h"
#include "CRS.h"
#include "CCS.h"
#include "JDS.h"
#include "SampleMatrix.h"
#include "ReadMatrixFile.h"
#include "types.h"

int main()
{

    matrix ibm32 = read_dense_matrix("matrices/ibm32.mtx");

    CRSMatrix ibm32_crs = read_crs("matrices/ibm32.mtx");

    CRSMatrix ibm32_convert = to_crs(ibm32);

    assert(ibm32_crs.num_cols == ibm32_convert.num_cols);
    assert(ibm32_crs.num_rows == ibm32_convert.num_rows);
    assert(ibm32_crs.col_ind.size() == ibm32_convert.col_ind.size());
    assert(ibm32_crs.val.size() == ibm32_convert.val.size());
    assert(ibm32_crs.row_ptr.size() == ibm32_convert.row_ptr.size());

    for (unsigned int i = 0; i < ibm32_convert.col_ind.size(); i++)
    {
        assert(ibm32_crs.col_ind[i] == ibm32_convert.col_ind[i]);
        assert(ibm32_crs.val[i] == ibm32_convert.val[i]);
    }

    for (unsigned int i = 0; i < ibm32_convert.row_ptr.size(); i++)
    {
        assert(ibm32_crs.row_ptr[i] == ibm32_convert.row_ptr[i]);
    }

    matrix mat = {{0., 1., 2.}, {1., 2., 3.}, {0., -12., 9.}, {3., 2., 7.}};

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

    auto jds = to_jds(jds_test);

    std::cout << "jdiag: ";
    for (unsigned int i = 0; i < jds.jdiag.size(); i++)
    {
        std::cout << jds.jdiag[i] << " ";
    }
    std::cout << '\n';

    std::cout << "col_ind: ";
    for (unsigned int i = 0; i < jds.col_ind.size(); i++)
    {
        std::cout << jds.col_ind[i] << " ";
    }
    std::cout << '\n';

    std::cout << "perm: ";
    for (unsigned int i = 0; i < jds.perm.size(); i++)
    {
        std::cout << jds.perm[i] << " ";
    }
    std::cout << '\n';

    std::cout << "jd_ptr: ";
    for (unsigned int i = 0; i < jds.jd_ptr.size(); i++)
    {
        std::cout << jds.jd_ptr[i] << " ";
    }
    std::cout << '\n';

    auto reconstruct_jds = from_jds(jds);

    for (unsigned int i = 0; i < reconstruct_jds.size(); i++)
    {
        for (unsigned int j = 0; j < reconstruct_jds[i].size(); j++)
        {
            std::cout << reconstruct_jds[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}