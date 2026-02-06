#ifndef CCS_H
#define CCS_H

#include <vector>

struct CCSMatrix
{
    std::vector<double> val;
    std::vector<unsigned int> row_ind;
    std::vector<unsigned int> col_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
    unsigned int non_zero;
};

struct CCSMatrix to_ccs(const std::vector<std::vector<double>> mat);
std::vector<std::vector<double>> from_ccs(const struct CCSMatrix crs);

std::vector<double> ccs_vector_mult(struct CCSMatrix ccs, std::vector<double> vec);

#endif