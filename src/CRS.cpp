#include "CRS.h"

CRSMatrix to_crs(std::vector<std::vector<float>> mat)
{
    struct CRSMatrix out;

    out.val = std::vector<float>();

    for (unsigned int i = 0; i < mat.size(); i++)
    {
        out.row_ptr.push_back(out.val.size());
        for (unsigned int j = 0; j < mat[0].size(); j++)
        {
            if (mat[i][j] == 0.)
            {
                continue;
            }

            out.val.push_back(mat[i][j]);
            out.col_ind.push_back(j);
        }
    }

    return out;
}