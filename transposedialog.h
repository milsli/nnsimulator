#ifndef TRANSPOSEDIALOG_H
#define TRANSPOSEDIALOG_H

#include <QDialog>
#include "commons.h"

class QPushButton;
class QBoxLayout;
class QSpinBox;
class QFrame;

class TransposeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TransposeDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~TransposeDialog();

private:
    void setupView();
    void setupTopWidget(QWidget *widget);
    void setupCentralWidget(QWidget *widget);
    void setupMatrixFrame(QFrame *frame, FloatLineEditMatrix *widgetMatrix, const int rows, const int cols);
    void clearFloatLineEditMatrix(FloatLineEditMatrix *editMatrix);

signals:

private slots:
    void newMatrixSize();
    void prepareTransposeMatrix();

private:
    QWidget *topWidget;
    QWidget *mainWidget;
    QPushButton *closeButton;
    QBoxLayout *mainLayout;

    QFrame *inputMatrixFrame;
    QFrame *resultMatrixFrame;

    QSpinBox *columnsBox;
    QSpinBox *rowsBox;

    uint8_t matrixRows;
    uint8_t matrixCols;

    FloatLineEditMatrix *inputWidgetMatrix;
    FloatLineEditMatrix *resultWidgetMatrix;
};

#endif // TRANSPOSEDIALOG_H
