#ifndef CRS_H
#define CRS_H

#include <vector>
#include "types.h"

struct CRSMatrix
{
    std::vector<double> val;
    std::vector<unsigned int> col_ind;
    std::vector<unsigned int> row_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
    unsigned int non_zero;
};

struct CRSMatrix to_crs(const matrix mat);
matrix from_crs(const struct CRSMatrix crs);
std::vector<double> crs_vector_mult(struct CRSMatrix crs, std::vector<double> vec);

#endif