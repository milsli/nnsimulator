#include "transposedialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>

TransposeDialog::TransposeDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
    , matrixRows(3)
    , matrixCols(3)
{
    setupView();
}

TransposeDialog::~TransposeDialog()
{
    clearFloatLineEditMatrix(inputWidgetMatrix);
    clearFloatLineEditMatrix(resultWidgetMatrix);
}

void TransposeDialog::setupView()
{
    topWidget = new QWidget;
    mainWidget = new QWidget;
    closeButton = new QPushButton("Close");

    setupTopWidget(topWidget);
    setupCentralWidget(mainWidget);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
    setLayout(mainLayout);
}

void TransposeDialog::setupTopWidget(QWidget *widget)
{
    const int width = 70;
    columnsBox = new QSpinBox;
    columnsBox->setRange(2,15);
    columnsBox->setMinimumWidth(width);
    columnsBox->setValue(matrixCols);

    rowsBox = new QSpinBox;
    rowsBox->setRange(2,15);
    rowsBox->setMinimumWidth(width);
    rowsBox->setValue(matrixRows);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(20);
    layout->addWidget(columnsBox);
    layout->addWidget(new QLabel(" X "));
    layout->addWidget(rowsBox);
    layout->addStretch();

    connect(columnsBox, &QSpinBox::valueChanged, this, &TransposeDialog::newMatrixSize);
    connect(rowsBox, &QSpinBox::valueChanged, this, &TransposeDialog::newMatrixSize);

    widget->setLayout(layout);
}

void TransposeDialog::setupCentralWidget(QWidget *widget)
{
    inputMatrixFrame = new QFrame;
    inputMatrixFrame->setFrameStyle(0x01);
    QPushButton *calculateButton = new QPushButton("transpose");
    resultMatrixFrame = new QFrame;
    resultMatrixFrame->setFrameStyle(0x01);

    inputWidgetMatrix = new FloatLineEditMatrix(matrixRows, std::vector<FloatLineEdit*>(matrixCols));
    resultWidgetMatrix = new FloatLineEditMatrix(matrixCols, std::vector<FloatLineEdit*>(matrixRows));

    setupMatrixFrame(inputMatrixFrame, inputWidgetMatrix, matrixRows, matrixCols);
    setupMatrixFrame(resultMatrixFrame, resultWidgetMatrix, matrixCols, matrixRows);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(inputMatrixFrame);
    layout->addWidget(calculateButton);
    layout->addWidget(resultMatrixFrame);

    connect(calculateButton, &QPushButton::clicked, this, &TransposeDialog::prepareTransposeMatrix);

    widget->setLayout(layout);
}

void TransposeDialog::setupMatrixFrame(QFrame *frame, FloatLineEditMatrix *widgetMatrix,const int rows, const int cols)
{
    QLayout *oldLayout = frame->layout();

    if (oldLayout != nullptr) {
        while (QLayoutItem* item = oldLayout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }

    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*widgetMatrix)[i][j] = new FloatLineEdit;
            layout->addWidget((*widgetMatrix)[i][j], i, j);
        }
    }

    frame->setLayout(layout);
    frame->update();
    frame->adjustSize();
}

void TransposeDialog::clearFloatLineEditMatrix(FloatLineEditMatrix *editMatrix)
{
    for (auto it = editMatrix->begin(); it != editMatrix->end(); ++it) {
        for (auto iti = it->begin(); iti != it->end(); ++iti) {
            (*iti)->deleteLater();
        }
    }

    delete editMatrix;
}

void TransposeDialog::newMatrixSize()
{
    matrixRows = rowsBox->value();
    matrixCols = columnsBox->value();

    clearFloatLineEditMatrix(inputWidgetMatrix);
    clearFloatLineEditMatrix(resultWidgetMatrix);

    inputWidgetMatrix = new FloatLineEditMatrix(matrixRows, std::vector<FloatLineEdit*>(matrixCols));
    resultWidgetMatrix = new FloatLineEditMatrix(matrixCols, std::vector<FloatLineEdit*>(matrixRows));

    setupMatrixFrame(inputMatrixFrame, inputWidgetMatrix, matrixRows, matrixCols);
    setupMatrixFrame(resultMatrixFrame, resultWidgetMatrix, matrixCols, matrixRows);
}

void TransposeDialog::prepareTransposeMatrix()
{
    // Matrix *matrix = new Matrix(matrixRows, std::vector<double>(matrixCols));
    // Matrix *resultMatrix = new Matrix(matrixCols, std::vector<double>(matrixRows));



    // for (int i = 0; i < matrixRows; ++i) {
    //     for (int j = 0; j < matrixCols; ++j) {
    //         (*matrix)[i][j] = (*inputWidgetMatrix)[i][j]->value();
    //     }
    // }

    // transposeMatrix(matrix, resultMatrix);

    // for (int i = 0; i < matrixCols; ++i) {
    //     for (int j = 0; j < matrixRows; ++j) {
    //         (*resultWidgetMatrix)[i][j]->setValue((*resultMatrix)[i][j]);
    //     }
    // }


    // delete matrix;
}

