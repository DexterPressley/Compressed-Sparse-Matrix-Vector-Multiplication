#include "ReadMatrixFile.h"
#include "TJDS.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include "CCS.h"
#include <algorithm>

matrix read_dense_matrix(std::string file_path)
{
    std::string line;
    std::ifstream file(file_path);

    assert(std::getline(file, line)); // ignore first line since it is a text header
    assert(std::getline(file, line));

    std::istringstream sizes(line);

    unsigned int rows, cols;

    assert(sizes >> rows >> cols); // ignore num nonzero elements we don't need that

    matrix output(rows, std::vector<double>(cols, 0));

    while (std::getline(file, line))
    {
        std::istringstream data(line);
        unsigned int row, col;
        if (!(data >> row >> col))
            continue; // skip malformed/empty lines

        double value;
        if (data >> value)
            output[row - 1][col - 1] = value;
        else
            output[row - 1][col - 1] = 1.;
    }

    return output;
}

CRSMatrix read_crs(std::string file_path)
{
    std::string line;
    std::ifstream file(file_path);

    assert(std::getline(file, line)); // ignore first line since it is a text header
    assert(std::getline(file, line));

    std::istringstream sizes(line);

    unsigned int rows, cols;

    assert(sizes >> rows >> cols); // ignore num nonzero elements we don't need that

    std::vector<std::vector<unsigned int>> row_index_list(rows, std::vector<unsigned int>());
    matrix row_value_list(rows, std::vector<double>());

    while (std::getline(file, line))
    {
        std::istringstream data(line);
        unsigned int row, col;
        if (!(data >> row >> col))
            continue;

        row_index_list[row - 1].push_back(col - 1);
        double value;
        if (data >> value)
            row_value_list[row - 1].push_back(value);
        else
            row_value_list[row - 1].push_back(1.);
    }

    CRSMatrix output;
    output.num_cols = cols;
    output.num_rows = rows;

    output.row_ptr = std::vector<unsigned int>();
    output.row_ptr.push_back(0);

    unsigned int sum = 0;
    for (std::vector<unsigned int> row : row_index_list)
    {
        sum += row.size();
        output.row_ptr.push_back(sum);
        for (unsigned int col : row)
        {
            output.col_ind.push_back(col);
        }
    }

    for (std::vector<double> row : row_value_list)
    {
        for (double value : row)
        {
            output.val.push_back(value);
        }
    }

    return output;
}

CCSMatrix read_ccs(std::string file_path)
{
    std::string line;
    std::ifstream file(file_path);

    assert(std::getline(file, line)); // ignore first line since it is a text header
    assert(std::getline(file, line));

    std::istringstream sizes(line);

    unsigned int rows, cols;

    assert(sizes >> rows >> cols); // ignore num nonzero elements we don't need that

    std::vector<std::vector<unsigned int>> col_index_list(cols, std::vector<unsigned int>());
    matrix col_value_list(cols, std::vector<double>());

    while (std::getline(file, line))
    {
        std::istringstream data(line);
        unsigned int row, col;
        if (!(data >> row >> col))
            continue;

        col_index_list[col - 1].push_back(row - 1);
        double value;
        if (data >> value)
            col_value_list[col - 1].push_back(value);
        else
            col_value_list[col - 1].push_back(1.);
    }

    CCSMatrix output;
    output.num_cols = cols;
    output.num_rows = rows;

    output.col_ptr = std::vector<unsigned int>();
    output.col_ptr.push_back(0);

    unsigned int sum = 0;
    for (std::vector<unsigned int> col : col_index_list)
    {
        sum += col.size();
        output.col_ptr.push_back(sum);
        for (unsigned int row : col)
        {
            output.row_ind.push_back(row);
        }
    }

    for (std::vector<double> col : col_value_list)
    {
        for (double value : col)
        {
            output.val.push_back(value);
        }
    }

    return output;
}

TJDSMatrix read_tjds(std::string file_path)
{
    std::string line;
    std::ifstream file(file_path);

    assert(std::getline(file, line)); // ignore first line since it is a text header
    assert(std::getline(file, line));

    std::istringstream sizes(line);

    unsigned int rows, cols;

    assert(sizes >> rows >> cols); // ignore num nonzero elements we don't need that

    std::vector<std::vector<unsigned int>> col_index_list(cols, std::vector<unsigned int>());
    matrix col_value_list(cols, std::vector<double>());

    while (std::getline(file, line))
    {
        std::istringstream data(line);
        unsigned int row, col;
        if (!(data >> row >> col))
            continue;

        col_index_list[col - 1].push_back(row - 1);
        double value;
        if (data >> value)
            col_value_list[col - 1].push_back(value);
        else
            col_value_list[col - 1].push_back(1.);
    }

    struct TJDSMatrix out;
    out.jdiag = std::vector<double>();
    out.row_ind = std::vector<unsigned int>();
    out.perm = std::vector<unsigned int>();
    out.jd_ptr = std::vector<unsigned int>();
    out.num_rows = rows;
    out.num_cols = cols;
    if (out.num_rows == 0 || out.num_cols == 0)
        return out;

    std::vector<unsigned int> nonzeros{};
    for (auto col : col_value_list)
    {
        nonzeros.push_back(col.size());
    }

    std::vector<unsigned int> forward_perm = permute_descending(nonzeros);

    // Store forward permutation as 1-based in out.perm
    for (unsigned int j = 0; j < forward_perm.size(); j++)
    {
        out.perm.push_back(forward_perm[j] + 1); // Convert to 1-based
    }

    unsigned int max_nonzeros = 0;
    for (unsigned int j = 0; j < nonzeros.size(); j++)
        if (nonzeros[j] > max_nonzeros)
            max_nonzeros = nonzeros[j];

    if (max_nonzeros == 0)
    {
        out.jd_ptr.push_back(1);
        return out;
    }

    // permute cols and indices
    // std::vector<std::vector<std::pair<unsigned int, double>>> columns(out.num_cols);

    // for (unsigned int i = 0; i < cols; i++)
    // {
    //     for (unsigned int j = 0; j < col_value_list[i].size(); j++)
    //     {
    //         columns[i].push_back(std::make_pair(j, col_value_list[j][forward_perm[i]]));
    //     }
    // }

    for (unsigned int k = 0; k < max_nonzeros; k++)
    {
        out.jd_ptr.push_back(out.jdiag.size() + 1);
        for (unsigned int j = 0; j < out.num_cols; j++)
        {
            if (col_index_list[forward_perm[j]].size() > k)
            {
                // assert(col_index_list.size() > forward_perm[j]);
                // assert(col_value_list.size() > forward_perm[j]);
                // assert(col_index_list[forward_perm[j]].size() > k);
                // assert(col_value_list[forward_perm[j]].size() > k);
                out.row_ind.push_back(col_index_list[forward_perm[j]][k] + 1);
                out.jdiag.push_back(col_value_list[forward_perm[j]][k]);
            }
        }
    }

    return out;
}
