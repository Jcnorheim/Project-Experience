#include <string.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "sys/stat.h"


Matrix::Matrix(int i, int j) : rows( i ), cols( j ) {
    data = new float*[rows];
    for (int k = 0; k < rows; k++) {
        data[k] = new float[cols];
        for (int l = 0; l < cols; l++)
            data[k][l] = 0;
    }
}

Matrix Matrix::readMatrix( std::string filename ) {
    std::string token;
    std::ifstream file(filename.c_str());

    std::string line;
    std::getline(file, line);
    std::stringstream lineStream(line);

    lineStream >> token;
    int rows = atoi((const char *) token.c_str());
    lineStream >> token;
    int cols = atoi((const char *) token.c_str());

    Matrix *m = new Matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        std::getline(file, line);
        std::stringstream lineStream(line);
        for (int j = 0; j < cols; j++) {
            lineStream >> token;
            *(m->access(i, j)) = atof((const char *) token.c_str());
//            printf("reading...\n");
//            t = t->next;
        }
    }

    return *m;
}

float* Matrix::access(const int i, const int j) const {
    float *f = &data[i][j];
    return f;
}

Matrix::Matrix(const Matrix& m) {
    rows = *(new int(m.rows));
    cols = *(new int(m.cols));

    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++)
            data[i][j] = *(new float(m.data[i][j]));
    }
}

int Matrix::numRows() {
    return rows;
}

int Matrix::numCols() {
    return cols;
}

std::ostream& operator<<(std::ostream &os, Matrix &m) {
    os << m.rows << " " << m.cols << "\n";
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            os << m.data[i][j] << "  ";
        os << "\n";
    }
    return os;
}
