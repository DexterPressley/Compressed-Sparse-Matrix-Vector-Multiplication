#include "CCS.h"
#include <cassert>

CCSMatrix to_ccs(matrix mat)
{
    struct CCSMatrix out;

    out.num_rows = mat.size();
    out.num_cols = mat[0].size();
    out.non_zero = 0;

    out.val = std::vector<double>();

    for (unsigned int i = 0; i < out.num_cols; i++)
    {
        out.col_ptr.push_back(out.val.size());
        for (unsigned int j = 0; j < out.num_rows; j++)
        {
            if (mat[j][i] == 0.)
            {
                continue;
            }

            out.non_zero++;
            out.val.push_back(mat[j][i]);
            out.row_ind.push_back(j);
        }
    }

    out.col_ptr.push_back(out.val.size());

    return out;
}

matrix from_ccs(CCSMatrix ccs)
{
    matrix
        output(ccs.num_rows, std::vector<double>(ccs.num_cols, 0));

    for (unsigned int i = 0; i < ccs.col_ptr.size() - 1; i++)
    {
        for (unsigned int j = ccs.col_ptr[i]; j < ccs.col_ptr[i + 1]; j++)
        {
            output[ccs.row_ind[j]][i] = ccs.val[j];
        }
    }

    return output;
}

std::vector<double> ccs_vector_mult(CCSMatrix ccs, std::vector<double> vec)
{

    assert(vec.size() == ccs.num_cols);

    std::vector<double> output(ccs.num_rows, 0);

    for (unsigned int i = 0; i < ccs.col_ptr.size() - 1; i++)
    {
        for (unsigned int j = ccs.col_ptr[i]; j < ccs.col_ptr[i + 1]; j++)
        {
            output[ccs.row_ind[j]] += vec[i] * ccs.val[j];
        }
    }

    return output;
}
