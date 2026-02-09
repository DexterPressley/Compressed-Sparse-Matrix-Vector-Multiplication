#include "TJDS.h"

static std::vector<unsigned int> per_col_nonzeros(const std::vector<std::vector<float>>& mat)
{
    // For each column, increment a counter for each non-zero value stored in the matrix and assign that column's nonzero counter in the output vector.
    unsigned int num_cols;
    if(mat.empty())
    {
        num_cols = 0;
    } 
    else 
    {
        num_cols = mat[0].size();
    }
    std::vector<unsigned int> nonzeros(num_cols);
    for (unsigned int j = 0; j < num_cols; j++)
    {
        unsigned int counter = 0;
        for (unsigned int i = 0; i < mat.size(); i++)
        {
            if (mat[i][j] == 0.)
            {
                continue;
            }
            counter++;
        }
        nonzeros[j] = counter;
    }
    return nonzeros;
}

static std::vector<unsigned int> permute_descending(std::vector<unsigned int> nonzeros)
{
    // Use selection sort to set indices in nonzero-count-descending order.
    std::vector<unsigned int> permutation(nonzeros.size());
    for (unsigned int i = 0; i < permutation.size(); i++) 
    {
        permutation[i] = i;
    }
    
    for (unsigned int i = 0; i < permutation.size(); i++)
    {
        unsigned int max_idx = i;
        for (unsigned int j = i + 1; j < permutation.size(); j++)
        {
            if (nonzeros[permutation[j]] > nonzeros[permutation[max_idx]])
            {
                max_idx = j;
            }
        }
        
        if (max_idx != i)
        {
            unsigned int temp = permutation[i];
            permutation[i] = permutation[max_idx];
            permutation[max_idx] = temp;
        }
    }
    
    return permutation;
}

TJDSMatrix to_tjds(std::vector<std::vector<float>> mat)
{
    struct TJDSMatrix out;
    out.jdiag = std::vector<float>();
    out.row_ind = std::vector<unsigned int>();
    out.perm = std::vector<unsigned int>();
    out.jd_ptr = std::vector<unsigned int>();
    out.num_rows = mat.size();
    out.num_cols = mat.empty() ? 0 : mat[0].size();
    if (out.num_rows == 0 || out.num_cols == 0) return out;
    
    std::vector<unsigned int> nonzeros = per_col_nonzeros(mat);
    std::vector<unsigned int> forward_perm = permute_descending(nonzeros);
    
    // Store forward permutation as 1-based in out.perm
    for (unsigned int j = 0; j < forward_perm.size(); j++)
    {
        out.perm.push_back(forward_perm[j] + 1);  // Convert to 1-based
    }
    
    unsigned int max_nonzeros = 0;
    for (unsigned int j = 0; j < nonzeros.size(); j++) 
        if (nonzeros[j] > max_nonzeros) max_nonzeros = nonzeros[j];
    
    if (max_nonzeros == 0)
    {
        out.jd_ptr.push_back(1);
        return out;
    }
    
    std::vector<std::vector<std::pair<unsigned int, float>>> cols(out.num_cols);
    for (unsigned int j = 0; j < out.num_cols; j++)
    {
        unsigned int orig = forward_perm[j];
        cols[j].reserve(nonzeros[orig]);
        for (unsigned int i = 0; i < out.num_rows; i++)
        {
            if (mat[i][orig] == 0.) continue;
            cols[j].push_back(std::make_pair(i, mat[i][orig]));
        }
    }
    
    for (unsigned int k = 0; k < max_nonzeros; k++)
    {
        out.jd_ptr.push_back(out.jdiag.size() + 1);
        for (unsigned int j = 0; j < out.num_cols; j++)
        {
            if (cols[j].size() > k)
            {
                out.row_ind.push_back(cols[j][k].first + 1);
                out.jdiag.push_back(cols[j][k].second);
            }
        }
    }
    
    return out;
}

std::vector<std::vector<float>> from_tjds(struct TJDSMatrix tjds)
{
    std::vector<std::vector<float>> output(tjds.num_rows, std::vector<float>(tjds.num_cols, 0));
    if (tjds.num_rows == 0 || tjds.num_cols == 0)
    {
        return output;
    }
    
    unsigned int num_diags = tjds.jd_ptr.size();
    
    for (unsigned int j = 0; j < tjds.num_cols; j++)
    {
        unsigned int orig = tjds.perm[j] - 1;  // Convert from 1-based to 0-based
        for (unsigned int k = 0; k < num_diags; k++)
        {
            unsigned int start = tjds.jd_ptr[k] - 1;
            unsigned int end;
            if(k + 1 < tjds.jd_ptr.size())
            {
                end = tjds.jd_ptr[k + 1] - 1;
            } 
            else 
            {
                end = tjds.jdiag.size();
            }
            unsigned int len = end - start;
            if (j < len)
            {
                unsigned int idx = start + j;
                unsigned int row = tjds.row_ind[idx] - 1;
                output[row][orig] = tjds.jdiag[idx];
            }
        }
    }
    
    return output;
}
