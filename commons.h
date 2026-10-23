#ifndef COMMONS_H
#define COMMONS_H

#include <vector>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLocale>

class FloatLineEdit;

//using Matrix = std::vector<std::vector<double>>;
using FloatLineEditMatrix = std::vector<std::vector<FloatLineEdit*>>;


class Matrix
{
public:
    Matrix(const uint16_t columns);     // używany do definicji wektowa wyjściowego (tylko 1 kolumna - tak na prawdę wiersz)
    Matrix(const uint16_t rows, const uint16_t columns);

    void setInput(const QList<double> & list);
    void setInput(const QList<double> && list);     // być może przenoszenie w back propagation będzie nieodpowiednie (tylko dla ciągu wejściowego)

    void setRandomValues();
    void wagsNormalization();
    // operator * nie ma charakteru ogólnego - wywoływany z macierzy [1,x] w celu wygenetowania odpowiedzi [1,y]. Ponadto uwzględnia BIAS
    Matrix operator*(const Matrix &matrix);

    double* operator[](size_t  row);
    const double* operator[](size_t  row) const;


private:
    int rows_;
    int columns_;
    QList<double> matrixData_;
};

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
