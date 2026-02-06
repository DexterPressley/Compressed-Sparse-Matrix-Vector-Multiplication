#include "ReadMatrixFile.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

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
        // read in each space separated string into a vector
        std::vector<std::string> inputs{};
        std::string current_word = "";
        for (unsigned int chr = 0; chr < line.size(); chr++)
        {
            if (isspace(line[chr]))
            {
                inputs.push_back(current_word);
                current_word = "";
                continue;
            }
            current_word += line[chr];
        }
        inputs.push_back(current_word);

        std::istringstream data(line);
        unsigned int row, col;
        assert(data >> row >> col);
        output[row - 1][col - 1] = 1.; // i have to do these stupid -1s because it starts counting from 1

        if (inputs.size() == 3) // row index, column index, value
        {
            double value;
            assert(data >> value);
            output[row - 1][col - 1] = value;
        }
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
        // read in each space separated string into a vector
        std::vector<std::string> inputs{};
        std::string current_word = "";
        for (unsigned int chr = 0; chr < line.size(); chr++)
        {
            if (isspace(line[chr]))
            {
                inputs.push_back(current_word);
                current_word = "";
                continue;
            }
            current_word += line[chr];
        }
        inputs.push_back(current_word);

        std::istringstream data(line);
        unsigned int row, col;
        assert(data >> row >> col);
        row_index_list[row - 1].push_back(col - 1);
        if (inputs.size() == 2)
        {
            row_value_list[row - 1].push_back(1.);
        }

        if (inputs.size() == 3) // row index, column index, value
        {
            double value;
            assert(data >> value);
            row_value_list[row - 1].push_back(value);
        }
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

// CRSMatrix read_crs(std::string file_path)
// {
//     return CRSMatrix();
// }
