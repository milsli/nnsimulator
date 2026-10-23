#include "commons.h"
#include <random>

// void multiplyMatrixes(Matrix *firstMatrix, Matrix *secondMatrix, Matrix *resultMatrix)
// {
//     uint16_t chunksNumber = (*firstMatrix)[0].size();
//     uint16_t resultMatrixRows = (*firstMatrix).size();
//     uint16_t resultMatrixCols = (*secondMatrix)[0].size();


//     for (uint16_t i = 0; i < resultMatrixRows; ++i) {
//         for (uint16_t j = 0; j < resultMatrixCols; ++j) {
//             double sum = 0.0;
//             for (uint16_t k = 0; k < chunksNumber; ++k) {
//                 sum += (*firstMatrix)[i][k] * (*secondMatrix)[k][j];
//             }
//             (*resultMatrix)[i][j] = sum;
//         }
//     }
// }

// void transposeMatrix(Matrix *inputMatrix, Matrix *resultMatrix)
// {
//     uint16_t matrixRows = inputMatrix->size();
//     uint16_t matrixCols = (*inputMatrix)[0].size();

//     for (uint16_t i = 0; i < matrixRows; ++i) {
//         for (uint16_t j = 0; j < matrixCols; ++j) {
//             (*resultMatrix)[j][i] = (*inputMatrix)[i][j];
//         }
//     }
// }

Matrix::Matrix(const uint16_t columns)
    : rows_(1)
    , columns_(columns)
    , matrixData_(columns_)
{
}

Matrix::Matrix(const uint16_t rows, const uint16_t columns)
    : rows_(rows)
    , columns_(columns)
    , matrixData_(rows_ * columns_)
{
}

void Matrix::setInput(const QList<double> &list)
{
    matrixData_ = list;
}

void Matrix::setInput(const QList<double> &&list)
{
    matrixData_ = list;
}

void Matrix::setRandomValues()
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::normal_distribution<> dist(0, 1);

    uint16_t indexes = matrixData_.size();
    for (uint16_t idx = 0; idx < indexes; ++idx) {
        matrixData_[idx] = dist(rd);
    }
}

void Matrix::wagsNormalization()
{

}

Matrix Matrix::operator*(const Matrix &matrix)
{
    // this - to macierz reprezentująca warstwę neuronów a matrix - wektor danych wejściowych
    assert(columns_ == matrix.columns_);    // liczba kolumn 1-szej macierzy == liczbie kolumn (!) 2-giej macierzy

    assert( matrix.rows_ == 1);

    //                 (3) 2 6 7
    //                 (7) 3 5 6
    //  (1) 2 4 6   *  (2) 4 1 1   =  x1 x2 x3 x4 x5
    //                 (3) 8 1 3
    //                 (4) 1 9 8

    Matrix output(1, rows_);
    for (uint16_t i = 0; i < rows_; ++i) {
        double sum = 0.0;
        for (uint16_t j = 0; j < columns_; ++j) {
            sum += matrixData_[(i * columns_) + j] * matrix.matrixData_[j];
        }
        output[0][i] = sum;
    }

    return output;
}

double* Matrix::operator[](size_t  row)
{
    return &matrixData_[row * columns_];
}

const double* Matrix::operator[](size_t  row) const
{
    return &matrixData_[row * columns_];
}
