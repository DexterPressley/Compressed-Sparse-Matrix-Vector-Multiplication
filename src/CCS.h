#ifndef CCS_H
#define CCS_H

#include <vector>

struct CCSMatrix
{
    std::vector<float> val;
    std::vector<unsigned int> row_ind;
    std::vector<unsigned int> col_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
    unsigned int non_zero;
};

struct CCSMatrix to_ccs(const std::vector<std::vector<float>> mat);
std::vector<std::vector<float>> from_ccs(const struct CCSMatrix crs);

#endif