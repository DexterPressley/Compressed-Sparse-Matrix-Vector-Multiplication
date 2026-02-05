#ifndef CRS_H
#define CRS_H

#include <vector>

struct CRSMatrix
{
    std::vector<float> val;
    std::vector<unsigned int> col_ind;
    std::vector<unsigned int> row_ptr;
};

struct CRSMatrix to_crs(std::vector<std::vector<float>> mat);
std::vector<std::vector<float>> from_crs(struct CRSMatrix crs);

#endif