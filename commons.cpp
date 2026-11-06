#include "commons.h"

Matrix operator-(const int cnt, const Matrix &mat)
{
    int rows = mat.rows();
    int columns = mat.columns();
    Matrix output(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            output[i][j] = cnt - mat[i][j];
        }
    }
    return output;
}

Matrix operator*(const double cnt, const Matrix &mat)
{
    int rows = mat.rows();
    int columns = mat.columns();
    Matrix output(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            output[i][j] = cnt * mat[i][j];
        }
    }
    return output;
}

