#ifndef MULTIPLYDIALOG_H
#define MULTIPLYDIALOG_H

#include <QDialog>
#include "commons.h"

class QPushButton;
class QBoxLayout;
class QSpinBox;
class QFrame;

class MultiplyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MultiplyDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~MultiplyDialog();

private:
    void setupView();
    void setupTopWidget(QWidget *widget);
    void setupCentralWidget(QWidget *widget);
    void setupMatrixFrame(QFrame *frame, FloatLineEditMatrix *widgetMatrix, const int rows, const int cols);
    void clearFloatLineEditMatrix(FloatLineEditMatrix *editMatrix);
    //void multiplyMatrixes(Matrix *firstMatrix, Matrix *secondMatrix, Matrix *resultMatrix);

private slots:
    void newFirstMatrixSize();
    void prepareMultiplyMatrixes();

private:
    QWidget *topWidget;
    QWidget *mainWidget;
    QPushButton *closeButton;
    QBoxLayout *mainLayout;

    QFrame *firstMatrixFrame;
    QFrame *secondMatrixFrame;
    QFrame *resultMatrixFrame;

    QSpinBox *firstColumnsBox;
    QSpinBox *firstRowsBox;
    QSpinBox *secondColumnsBox;
    QSpinBox *secondRowsBox;

    uint8_t firstMatrixRows;
    uint8_t firstMatrixCols;
    uint8_t secondMatrixRows;
    uint8_t secondMatrixCols;

    FloatLineEditMatrix *firstWidgetMatrix;
    FloatLineEditMatrix *secondWidgetMatrix;
    FloatLineEditMatrix *resultWidgetMatrix;
};

#endif // MULTIPLYDIALOG_H
