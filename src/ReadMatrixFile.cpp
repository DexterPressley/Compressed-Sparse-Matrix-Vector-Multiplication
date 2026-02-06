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

// CRSMatrix read_crs(std::string file_path)
// {
//     return CRSMatrix();
// }
