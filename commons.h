#ifndef COMMONS_H
#define COMMONS_H

#include <vector>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLocale>
#include <random>

class FloatLineEdit;

//using Matrix = std::vector<std::vector<double>>;
using FloatLineEditMatrix = std::vector<std::vector<FloatLineEdit*>>;


template <typename T>
class MatrixTemplate
{
public:
    MatrixTemplate(const uint16_t columns)     // używany do definicji wektowa wyjściowego (tylko 1 kolumna - tak na prawdę wiersz)
    : rows_(1)
    , columns_(columns)
    , matrixData_(columns_)
{

}

    MatrixTemplate(const uint16_t rows, const uint16_t columns)
        : rows_(rows)
        , columns_(columns)
        , matrixData_(rows_ * columns_)
    {

    }

    void setInput(const QList<double> & list)
    {
        matrixData_ = list;
    }

    void setInput(const QList<double> && list)     // być może przenoszenie w back propagation będzie nieodpowiednie (tylko dla ciągu wejściowego)
    {
        matrixData_ = list;
    }

    void setRandomValues()
    {
        std::random_device rd;
        std::mt19937 e2(rd());
        std::normal_distribution<> dist(0, 1);

        uint16_t indexes = matrixData_.size();
        for (uint16_t idx = 0; idx < indexes; ++idx) {
            matrixData_[idx] = dist(rd);
        }
        int y = 0;
        ++y;
    }

    void normalization()
    {
        // normalizacja ma na celu "spłaszczenia wartości do zakresu <-1,1>"
        // algorytm:
        // 0. wyznaczanie min i max
        // 1. obliczanie r = max - min, połowa = r/2
        // 2. poprawka = max - połowa;
        // 3. od wyszyskich elementów odejmij poprawkę - osiągnięta równowaga dla ujemnych i dodatnich
        // 4. podzielenie wszystkich wartości przez połowę

        for (int i = 0; i < rows_; ++i) {
            T min = matrixData_[i], max = matrixData_[i];
            for (int j = i * columns_; j < ((i + 1) * columns_); ++j) {
                if (min > matrixData_[j])
                    min = matrixData_[j];
                if (max < matrixData_[j])
                    max = matrixData_[j];
            }
            T half = (max - min) / 2.0;
            T adjustment = max - half;

            for (int j = i * columns_; j < ((i + 1) * columns_); ++j) {
                matrixData_[j] = (matrixData_[j] - adjustment) / half;
            }
        }

        int i = 0;
        ++i;
    }

    // operator * nie ma charakteru ogólnego - wywoływany z macierzy [1,x] w celu wygenetowania odpowiedzi [1,y]. Ponadto uwzględnia BIAS
    MatrixTemplate<T> operator*(const MatrixTemplate<T> &matrix)
    {
        // this - to macierz reprezentująca warstwę neuronów a matrix - wektor danych wejściowych
        assert(columns_ == matrix.columns_);    // liczba kolumn 1-szej macierzy == liczbie kolumn (!) 2-giej macierzy

        assert( matrix.rows_ == 1);

        //                 (3) 2 6 7
        //                 (7) 3 5 6
        //  (1) 2 4 6   *  (2) 4 1 1   =  x1 x2 x3 x4 x5
        //                 (3) 8 1 3
        //                 (4) 1 9 8

        MatrixTemplate<T> output(1, rows_);
        for (uint16_t i = 0; i < rows_; ++i) {
            double sum = 0.0;
            for (uint16_t j = 0; j < columns_; ++j) {
                sum += matrixData_[(i * columns_) + j] * matrix.matrixData_[j];
            }
            output[0][i] = sum;
        }

        return output;
    }

    T *operator [](size_t  row)
    {
        return &matrixData_[row * columns_];
    }

    const T* operator[](size_t  row) const
    {
        return &matrixData_[row * columns_];
    }



private:
    int rows_;
    int columns_;
    QList<T> matrixData_;
};

using Matrix = MatrixTemplate<double>;

class FloatLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit FloatLineEdit(QWidget *parent = nullptr)
    {
        QDoubleValidator *validator = new QDoubleValidator(this);
        validator->setNotation(QDoubleValidator::StandardNotation);
        QLocale cLocale(QLocale::C);
        validator->setLocale(cLocale);
        this->setValidator(validator);
        this->setText("0.0");
        this->setAlignment(Qt::AlignCenter);
        this->setMaximumWidth(45);
    }

    float value() const
    {
        QLocale cLocale(QLocale::C);
        return cLocale.toFloat(this->text());
    }

    void setValue(float val)
    {
        QLocale cLocale(QLocale::C);
        this->setText(cLocale.toString(val, 'f', 2));
    }
};

// void multiplyMatrixes(Matrix *firstMatrix, Matrix *secondMatrix, Matrix *resultMatrix);
// void transposeMatrix(Matrix *inputMatrix, Matrix *resultMatrix);

#endif // COMMONS_H
