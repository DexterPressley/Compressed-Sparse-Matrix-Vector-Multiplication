#ifndef JDS_H
#define JDS_H

#include <vector>

struct JDSMatrix
{
    std::vector<double> jdiag;
    std::vector<unsigned int> col_ind;
    std::vector<unsigned int> perm;
    std::vector<unsigned int> jd_ptr;
    unsigned int num_rows;
    unsigned int num_cols;
};

struct JDSMatrix to_jds(std::vector<std::vector<double>> mat);
std::vector<std::vector<double>> from_jds(struct JDSMatrix jds);
std::vector<double> jds_matrix_vector_mult(struct JDSMatrix jds, std::vector<double> x);

#endif