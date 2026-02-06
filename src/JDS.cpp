#include "JDS.h"

JDSMatrix to_jds(std::vector<std::vector<float>> mat)
{
    struct JDSMatrix out;

    out.jdiag = std::vector<float>();
    out.col_ind = std::vector<unsigned int>();
    out.perm = std::vector<unsigned int>();
    out.jd_ptr = std::vector<unsigned int>();

    for (unsigned int i = 0; i < mat.size(); i++)
    {
        out.jd_ptr.push_back(out.jdiag.size());
        for (unsigned int j = 0; j < mat[0].size(); j++)
        {
            if (mat[i][j] == 0.)
            {
                continue;
            }

            out.jdiag.push_back(mat[i][j]);
            out.col_ind.push_back(j);
        }
    }

    return out;
}