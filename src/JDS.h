#ifndef JDS_H
#define JDS_H

#include <vector>

struct JDSMatrix
{
    std::vector<float> jdiag;
    std::vector<unsigned int> col_ind;
    std::vector<unsigned int> perm;
    std::vector<unsigned int> jd_ptr;
};

struct JDSMatrix to_jds(std::vector<std::vector<float>> mat);
std::vector<std::vector<float>> from_jds(struct JDSMatrix jds);



struct JDSMatrix to_jds(std::vector<std::vector<float>> mat);
std::vector<std::vector<float>> from_jds(struct JDSMatrix jds);

#endif