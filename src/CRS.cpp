#include <cassert>
#include "CRS.h"
#include <iostream>

CRSMatrix to_crs(std::vector<std::vector<float>> mat)
{
    struct CRSMatrix out;

    out.num_rows = mat.size();
    out.num_cols = mat[0].size();
    out.non_zero = 0;

    out.val = std::vector<float>();

    for (unsigned int i = 0; i < out.num_rows; i++)
    {
        out.row_ptr.push_back(out.val.size());
        for (unsigned int j = 0; j < out.num_cols; j++)
        {
            if (mat[i][j] == 0.)
            {
                continue;
            }

            out.non_zero++;
            out.val.push_back(mat[i][j]);
            out.col_ind.push_back(j);
        }
    }

    out.row_ptr.push_back(out.val.size());

    return out;
}

std::vector<std::vector<float>> from_crs(CRSMatrix crs)
{
    std::vector<std::vector<float>>
        output(crs.num_rows, std::vector<float>(crs.num_cols, 0));

    for (unsigned int i = 0; i < crs.row_ptr.size() - 1; i++)
    {
        for (unsigned int j = crs.row_ptr[i]; j < crs.row_ptr[i + 1]; j++)
        {
            output[i][crs.col_ind[j]] = crs.val[j];
        }
    }

    return output;
}

std::vector<float> crs_vector_mult(CRSMatrix crs, std::vector<float> vec)
{
    assert(vec.size() == crs.num_cols);

    std::vector<float> output{};

    for (unsigned int i = 0; i < crs.row_ptr.size() - 1; i++)
    {
        float sum = 0;
        for (unsigned int j = crs.row_ptr[i]; j < crs.row_ptr[i + 1]; j++)
        {
            // std::cout << vec[crs.col_ind[j]] << " " << crs.val[j] << ' ' << vec[crs.col_ind[j]] * crs.val[j] << ' ';
            sum += vec[crs.col_ind[j]] * crs.val[j];
            // std::cout << output[crs.col_ind[j]] << '\n';
            // for (int i = 0; i < vec.size(); i++) {
            //     std::cout << '\t' << output[i];
            // }
            // std::cout << '\n';
        }

        output.push_back(sum);
    }

    return output;
}
