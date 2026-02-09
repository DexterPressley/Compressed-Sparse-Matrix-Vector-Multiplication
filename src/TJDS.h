#ifndef TJDS_H
#define TJDS_H

#include <vector>

struct TJDSMatrix
{
    std::vector<float> jdiag;
    std::vector<unsigned int> row_ind;
    std::vector<unsigned int> perm;
    std::vector<unsigned int> jd_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
};

struct TJDSMatrix to_tjds(std::vector<std::vector<float>> mat);
std::vector<std::vector<float>> from_tjds(struct TJDSMatrix tjds);

#endif
