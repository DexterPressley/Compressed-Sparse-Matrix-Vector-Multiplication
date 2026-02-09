#include <vector>
#include "CRS.h"
#include "TJDS.h"
#include <string>
#include "types.h"
#ifndef READ_MATRIX_FILE_H
#define READ_MATRIX_FILE_H

matrix read_dense_matrix(std::string file_path);
struct CRSMatrix read_crs(std::string file_path);
struct CCSMatrix read_ccs(std::string file_path);
struct TJDSMatrix read_tjds(std::string file_path);

#endif