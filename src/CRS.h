#ifndef CRS_H
#define CRS_H

#include <vector>

struct CRSMatrix
{
    std::vector<float> val;
    std::vector<unsigned int> col_ind;
    std::vector<unsigned int> row_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
    unsigned int non_zero;
};

struct CRSMatrix to_crs(const std::vector<std::vector<float>> mat);
std::vector<std::vector<float>> from_crs(const struct CRSMatrix crs);

#endif