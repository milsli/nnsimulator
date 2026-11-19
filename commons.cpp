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


bool product(Matrix *inout, const Matrix &in)
{
    int rows = inout->rows();
    int columns = inout->columns();
    assert(rows == in.rows());
    assert(columns == in.columns());

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            (*inout)[i][j] = (*inout)[i][j] * in[i][j];
        }
    }

    return true;
}

// pamiętać o  BIAS
Matrix* matrixMultiply(const Matrix &inout, const Matrix &in)
{
    // to "prawidłowe" mnożenie macierzy
    // w przyjętej w programie konwencji pierwsza z nich musi być transponowana
    assert(inout.columns() == in.rows());

    Matrix *output = new Matrix(inout.rows(), in.columns());

    for (int i = 0; i < inout.rows(); ++i) {
        for (int j = 0; j < in.columns(); ++j) {
            double sum = 0;
            for (int k = 0; k < in.rows(); ++k) {
                sum += inout[i][k] * in[k][j];
            }
            (*output)[i][j] = sum;
        }
    }

    return output;
}
