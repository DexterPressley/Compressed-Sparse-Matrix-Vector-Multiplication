#ifndef TJDS_H
#define TJDS_H

#include <vector>

struct TJDSMatrix
{
    std::vector<double> jdiag;
    std::vector<unsigned int> row_ind;
    std::vector<unsigned int> perm;
    std::vector<unsigned int> jd_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
};

struct TJDSMatrix to_tjds(std::vector<std::vector<double>> mat);
std::vector<std::vector<double>> from_tjds(struct TJDSMatrix tjds);
std::vector<double> tjds_matrix_vector_mult(struct TJDSMatrix tjds, std::vector<double> x);
std::vector<unsigned int> permute_descending(std::vector<unsigned int> nonzeros);

#endif
