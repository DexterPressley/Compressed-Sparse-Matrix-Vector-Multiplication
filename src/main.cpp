#include <iostream>
#include <cassert>
#include "Matrix.h"
#include "CRS.h"
#include "CCS.h"
#include "JDS.h"
#include "TJDS.h"
#include "SampleMatrix.h"
#include "ReadMatrixFile.h"
#include "types.h"
#include <chrono>

void problem_1()
{
    // CRS

    CRSMatrix crs = to_crs(problem_1_mat);

    std::cout << "CRS Data Structures\n";

    std::cout
        << "val:\t";
    for (unsigned int i = 0; i < crs.val.size(); i++)
    {
        std::cout << crs.val[i] << ',';
    }
    std::cout << '\n';

    std::cout << "col_ind:\t";
    for (unsigned int i = 0; i < crs.col_ind.size(); i++)
    {
        std::cout << crs.col_ind[i] + 1 << ',';
    }
    std::cout << '\n';

    std::cout << "row_ptr:\t";
    for (unsigned int i = 0; i < crs.row_ptr.size(); i++)
    {
        std::cout << crs.row_ptr[i] + 1 << ',';
    }
    std::cout << '\n';
    std::cout << '\n';

    // CCS

    CCSMatrix ccs = to_ccs(problem_1_mat);

    std::cout << "CCS Data Structures\n";

    std::cout
        << "val:\t";
    for (unsigned int i = 0; i < ccs.val.size(); i++)
    {
        std::cout << ccs.val[i] << ',';
    }
    std::cout << '\n';

    std::cout << "row_ind:\t";
    for (unsigned int i = 0; i < ccs.row_ind.size(); i++)
    {
        std::cout << ccs.row_ind[i] + 1 << ',';
    }
    std::cout << '\n';

    std::cout << "col_ptr:\t";
    for (unsigned int i = 0; i < ccs.col_ptr.size(); i++)
    {
        std::cout << ccs.col_ptr[i] + 1 << ',';
    }
    std::cout << '\n';
    std::cout << '\n';

    JDSMatrix jds = to_jds(problem_1_mat);

    std::cout << "JDS Data Structures\n";

    std::cout
        << "jdiag:\t";
    for (unsigned int i = 0; i < jds.jdiag.size(); i++)
    {
        std::cout << jds.jdiag[i] << ',';
    }
    std::cout << '\n';

    std::cout << "row_ind:\t";
    for (unsigned int i = 0; i < jds.col_ind.size(); i++)
    {
        std::cout << jds.col_ind[i] << ',';
    }
    std::cout << '\n';

    std::cout << "jd_ptr:\t";
    for (unsigned int i = 0; i < jds.jd_ptr.size(); i++)
    {
        std::cout << jds.jd_ptr[i] << ',';
    }
    std::cout << '\n';

    std::cout << "perm:\t";
    for (unsigned int i = 0; i < jds.perm.size(); i++)
    {
        std::cout << jds.perm[i] << ',';
    }
    std::cout << '\n';
    std::cout << '\n';

    TJDSMatrix tjds = to_tjds(problem_1_mat);
    std::cout << "TJDS Data Structures\n";

    std::cout
        << "jdiag:\t";
    for (unsigned int i = 0; i < tjds.jdiag.size(); i++)
    {
        std::cout << tjds.jdiag[i] << ',';
    }
    std::cout << '\n';

    std::cout << "row_ind:\t";
    for (unsigned int i = 0; i < tjds.row_ind.size(); i++)
    {
        std::cout << tjds.row_ind[i] << ',';
    }
    std::cout << '\n';

    std::cout << "jd_ptr:\t";
    for (unsigned int i = 0; i < tjds.jd_ptr.size(); i++)
    {
        std::cout << tjds.jd_ptr[i] << ',';
    }
    std::cout << '\n';

    std::cout << "perm:\t";
    for (unsigned int i = 0; i < tjds.perm.size(); i++)
    {
        std::cout << tjds.perm[i] << ',';
    }
    std::cout << '\n';
    std::cout << '\n';
}

void problem_2()
{
    std::vector<double> x(32, 1.);

    matrix ibm32 = read_dense_matrix("matrices/ibm32.mtx");

    auto t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 1000; i++)
    {
        std::vector<double> ans = matrix_vector_mult(ibm32, x);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "IBM32 dense matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 1000 iterations\n";

    t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 10000; i++)
    {
        std::vector<double> ans = matrix_vector_mult(ibm32, x);
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "IBM32 dense matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 10000 iterations\n";
}

void problem_3()
{
    std::vector<double> x(32, 1.);

    CRSMatrix ibm32 = read_crs("matrices/ibm32.mtx");

    auto t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 1000; i++)
    {
        std::vector<double> ans = crs_vector_mult(ibm32, x);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "IBM32 crs matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 1000 iterations\n";

    t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 10000; i++)
    {
        std::vector<double> ans = crs_vector_mult(ibm32, x);
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "IBM32 crs matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 10000 iterations\n";
}

void problem_4_1()
{
    CRSMatrix memplus = read_crs("matrices/memplus.mtx");
    std::vector<double> x(memplus.num_cols, 1.);

    auto t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 1000; i++)
    {
        std::vector<double> ans = crs_vector_mult(memplus, x);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "MEMPLUS crs matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 1000 iterations\n";

    t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 10000; i++)
    {
        std::vector<double> ans = crs_vector_mult(memplus, x);
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "MEMPLUS crs matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 10000 iterations\n";
}

void problem_4_2()
{
    TJDSMatrix memplus_tjds = read_tjds("matrices/memplus.mtx");
    std::vector<double> x(memplus_tjds.num_cols, 1.);

    auto t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 1000; i++)
    {
        std::vector<double> ans = tjds_matrix_vector_mult(memplus_tjds, x);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "MEMPLUS tjds matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 1000 iterations\n";

    t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < 10000; i++)
    {
        std::vector<double> ans = tjds_matrix_vector_mult(memplus_tjds, x);
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "MEMPLUS tjds matrix mult took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds for 10000 iterations\n";
}

<<<<<<< Updated upstream
int main()
{
    std::cout << "\n\nPROBLEM 1:\n\n";
    problem_1();
    std::cout << "\n\nPROBLEM 2:\n\n";
    problem_2();
    std::cout << "\n\nPROBLEM 3:\n\n";
    problem_3();
    std::cout << "\n\nPROBLEM 4:\n\n";
    problem_4_1();
    problem_4_2();
=======
    auto jds = to_jds(jds_test);

    std::cout << "\njdiag: ";
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

    auto jds1 = to_jds(decimal_test);
    // JDS matrix-vector multiplication example
    std::cout << "JDS matrix-vector multiplication:\n";
    std::vector<float> x = {1.0f, 2.0f, 3.0f};
    std::vector<float> y_jds = jds_matrix_vector_mult(jds1, x_test);
    std::cout << "x: ";
    for (unsigned int i = 0; i < x_test.size(); i++)
    {
        std::cout << x_test[i] << " ";
    }
    std::cout << "\ny: ";
    for (unsigned int i = 0; i < y_jds.size(); i++)
    {
        std::cout << y_jds[i] << " ";
    }
    std::cout << "\n\n";

    // TJDS matrix-vector multiplication example
    std::cout << "TJDS matrix-vector multiplication:\n";
    auto tjds = to_tjds(decimal_test);
    std::vector<float> y_tjds = tjds_matrix_vector_mult(tjds, x_test);
    std::cout << "x: ";
    for (unsigned int i = 0; i < x_test.size(); i++)
    {
        std::cout << x_test[i] << " ";
    }
    std::cout << "\ny: ";
    for (unsigned int i = 0; i < y_tjds.size(); i++)
    {
        std::cout << y_tjds[i] << " ";
    }
    std::cout << "\n";
>>>>>>> Stashed changes
}