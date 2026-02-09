#include "JDS.h"

static std::vector<unsigned int> per_row_nonzeros(const std::vector<std::vector<float>>& mat)
{
    // For each row, increment a counter for each non-zero value stored in the matrix and assign that row's nonzero counter in the output vector.
    std::vector<unsigned int> nonzeros(mat.size());
    for (unsigned int i = 0; i < mat.size(); i++)
    {
        unsigned int counter = 0;
        for (unsigned int j = 0; j < mat[i].size(); j++)
        {
            if (mat[i][j] == 0.)
            {
                continue;
            }
            counter++;
        }
        nonzeros[i] = counter;
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

JDSMatrix to_jds(std::vector<std::vector<float>> mat)
{
    struct JDSMatrix out;
    out.jdiag = std::vector<float>();
    out.col_ind = std::vector<unsigned int>();
    out.perm = std::vector<unsigned int>();
    out.jd_ptr = std::vector<unsigned int>();
    out.num_rows = mat.size();
    out.num_cols = mat.empty() ? 0 : mat[0].size();
    if (out.num_rows == 0 || out.num_cols == 0) return out;
    
    std::vector<unsigned int> nonzeros = per_row_nonzeros(mat);
    std::vector<unsigned int> forward_perm = permute_descending(nonzeros);
    
    // Store forward permutation as 1-based in out.perm
    for (unsigned int i = 0; i < forward_perm.size(); i++)
    {
        out.perm.push_back(forward_perm[i] + 1);  // Convert to 1-based
    }
    
    unsigned int max_nonzeros = 0;
    for (unsigned int i = 0; i < nonzeros.size(); i++) 
        if (nonzeros[i] > max_nonzeros) max_nonzeros = nonzeros[i];
    
    if (max_nonzeros == 0)
    {
        out.jd_ptr.push_back(1);
        return out;
    }
    
    std::vector<std::vector<std::pair<unsigned int, float>>> rows(out.num_rows);
    for (unsigned int i = 0; i < out.num_rows; i++)
    {
        unsigned int orig = forward_perm[i];
        rows[i].reserve(nonzeros[orig]);
        for (unsigned int j = 0; j < out.num_cols; j++)
        {
            if (mat[orig][j] == 0.) continue;
            rows[i].push_back(std::make_pair(j, mat[orig][j]));
        }
    }
    
    for (unsigned int k = 0; k < max_nonzeros; k++)
    {
        out.jd_ptr.push_back(out.jdiag.size() + 1);
        for (unsigned int i = 0; i < out.num_rows; i++)
        {
            if (rows[i].size() > k)
            {
                out.col_ind.push_back(rows[i][k].first + 1);
                out.jdiag.push_back(rows[i][k].second);
            }
        }
    }
    
    return out;
}

std::vector<std::vector<float>> from_jds(struct JDSMatrix jds)
{
    std::vector<std::vector<float>> output(jds.num_rows, std::vector<float>(jds.num_cols, 0));
    if (jds.num_rows == 0 || jds.num_cols == 0)
    {
        return output;
    }
    
    unsigned int num_diags = jds.jd_ptr.size();
    
    for (unsigned int i = 0; i < jds.num_rows; i++)
    {
        unsigned int orig = jds.perm[i] - 1;  // Convert from 1-based to 0-based
        for (unsigned int k = 0; k < num_diags; k++)
        {
            unsigned int start = jds.jd_ptr[k] - 1;
            unsigned int end;
            if(k + 1 < jds.jd_ptr.size())
            {
                end = jds.jd_ptr[k + 1] - 1;
            } 
            else 
            {
                end = jds.jdiag.size();
            }
            unsigned int len = end - start;
            if (i < len)
            {
                unsigned int idx = start + i;
                unsigned int col = jds.col_ind[idx] - 1;
                output[orig][col] = jds.jdiag[idx];
            }
        }
    }
    
    return output;
}

std::vector<float> jds_matrix_vector_mult(struct JDSMatrix jds, std::vector<float> x)
{
    std::vector<float> y(jds.num_rows, 0.0f);
    if (jds.num_rows == 0 || jds.num_cols == 0) return y;
    
    unsigned int num_diags = jds.jd_ptr.size();
    
    for (unsigned int i = 0; i < jds.num_rows; i++)
    {
        unsigned int orig = jds.perm[i] - 1;  // Convert from 1-based to 0-based
        for (unsigned int k = 0; k < num_diags; k++)
        {
            unsigned int start = jds.jd_ptr[k] - 1;
            unsigned int end;
            if(k + 1 < jds.jd_ptr.size())
            {
                end = jds.jd_ptr[k + 1] - 1;
            } 
            else 
            {
                end = jds.jdiag.size();
            }
            unsigned int len = end - start;
            if (i < len)
            {
                unsigned int idx = start + i;
                unsigned int col = jds.col_ind[idx] - 1;
                y[orig] += jds.jdiag[idx] * x[col];
            }
        }
    }
    
    return y;
}