#include "multiplydialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>

MultiplyDialog::MultiplyDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , firstMatrixRows(1)
    , firstMatrixCols(3)
    , secondMatrixRows(3)
    , secondMatrixCols(3)
{
    setupView();
}

MultiplyDialog::~MultiplyDialog()
{

}

void MultiplyDialog::setupView()
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

void MultiplyDialog::setupTopWidget(QWidget *widget)
{
    QFrame *leftFrame = new QFrame;
    leftFrame->setFrameStyle(0x01);
    QFrame *rightFrame = new QFrame;
    rightFrame->setFrameStyle(0x01);

    const int width = 70;

    firstRowsBox = new QSpinBox;
    firstRowsBox->setRange(1,15);
    firstRowsBox->setMinimumWidth(width);
    firstRowsBox->setValue(firstMatrixRows);
    firstRowsBox->setDisabled(true);

    firstColumnsBox = new QSpinBox;
    firstColumnsBox->setRange(1,15);
    firstColumnsBox->setMinimumWidth(width);
    firstColumnsBox->setValue(firstMatrixCols);

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(firstRowsBox);
    leftLayout->setSpacing(20);
    leftLayout->addWidget(new QLabel(" X "));
    leftLayout->addWidget(firstColumnsBox);
    leftLayout->addStretch();
    leftFrame->setLayout(leftLayout);

    secondRowsBox = new QSpinBox;
    secondRowsBox->setRange(1,15);
    secondRowsBox->setMinimumWidth(width);
    secondRowsBox->setValue(secondMatrixRows);

    secondColumnsBox = new QSpinBox;
    secondColumnsBox->setRange(1,15);
    secondColumnsBox->setMinimumWidth(width);
    secondColumnsBox->setValue(firstMatrixCols);
    secondColumnsBox->setEnabled(false);


    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->setSpacing(20);
    rightLayout->addWidget(secondRowsBox);
    rightLayout->addWidget(new QLabel(" X "));
    rightLayout->addWidget(secondColumnsBox);
    // leftLayout->addStretch();
    rightFrame->setLayout(rightLayout);


    connect(firstRowsBox, &QSpinBox::valueChanged, this, &MultiplyDialog::newFirstMatrixSize);
    connect(firstColumnsBox, &QSpinBox::valueChanged, [=]()
    {
        secondColumnsBox->setValue(firstColumnsBox->value());
        this->newFirstMatrixSize();
    });
    // connect(secondColumnsBox, &QSpinBox::valueChanged, this, &MultiplyDialog::newFirstMatrixSize);// to załatwiane poprzednim sygnałem
    connect(secondRowsBox, &QSpinBox::valueChanged, this, &MultiplyDialog::newFirstMatrixSize);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(30);
    layout->addWidget(leftFrame);
    layout->addWidget(rightFrame);
    layout->addStretch();

    widget->setLayout(layout);
}

void MultiplyDialog::setupCentralWidget(QWidget *widget)
{
    firstMatrixFrame = new QFrame;
    firstMatrixFrame->setFrameStyle(0x01);
    secondMatrixFrame = new QFrame;
    secondMatrixFrame->setFrameStyle(0x01);
    QPushButton *calculateButton = new QPushButton("multiply");
    resultMatrixFrame = new QFrame;
    resultMatrixFrame->setFrameStyle(0x01);

    firstWidgetMatrix = new FloatLineEditMatrix(firstMatrixRows, std::vector<FloatLineEdit*>(firstMatrixCols));
    secondWidgetMatrix = new FloatLineEditMatrix(secondMatrixRows, std::vector<FloatLineEdit*>(secondMatrixCols));
    resultWidgetMatrix = new FloatLineEditMatrix(firstMatrixRows, std::vector<FloatLineEdit*>(secondMatrixRows));

    setupMatrixFrame(firstMatrixFrame, firstWidgetMatrix, firstMatrixRows, firstMatrixCols);
    setupMatrixFrame(secondMatrixFrame, secondWidgetMatrix, secondMatrixRows, secondMatrixCols);
    setupMatrixFrame(resultMatrixFrame, resultWidgetMatrix, firstMatrixRows, secondMatrixRows);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(firstMatrixFrame);
    layout->addWidget(secondMatrixFrame);

    layout->addWidget(calculateButton);
    layout->addWidget(resultMatrixFrame);

    connect(calculateButton, &QPushButton::clicked, this, &MultiplyDialog::prepareMultiplyMatrixes);

    widget->setLayout(layout);
}

void MultiplyDialog::setupMatrixFrame(QFrame *frame, FloatLineEditMatrix *widgetMatrix, const int rows, const int cols)
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

void MultiplyDialog::clearFloatLineEditMatrix(FloatLineEditMatrix *editMatrix)
{
    for (auto it = editMatrix->begin(); it != editMatrix->end(); ++it) {
        for (auto iti = it->begin(); iti != it->end(); ++iti) {
            (*iti)->deleteLater();
        }
    }

    delete editMatrix;
}

void MultiplyDialog::newFirstMatrixSize()
{
    firstMatrixRows = firstRowsBox->value();
    firstMatrixCols = firstColumnsBox->value();
    secondMatrixRows = secondRowsBox->value();
    secondMatrixCols = secondColumnsBox->value();

    clearFloatLineEditMatrix(firstWidgetMatrix);
    clearFloatLineEditMatrix(secondWidgetMatrix);
    clearFloatLineEditMatrix(resultWidgetMatrix);

    firstWidgetMatrix = new FloatLineEditMatrix(firstMatrixRows, std::vector<FloatLineEdit*>(firstMatrixCols));
    secondWidgetMatrix = new FloatLineEditMatrix(secondMatrixRows, std::vector<FloatLineEdit*>(secondMatrixCols));
    resultWidgetMatrix = new FloatLineEditMatrix(firstMatrixRows, std::vector<FloatLineEdit*>(secondMatrixRows));

    setupMatrixFrame(firstMatrixFrame, firstWidgetMatrix, firstMatrixRows, firstMatrixCols);
    setupMatrixFrame(secondMatrixFrame, secondWidgetMatrix, secondMatrixRows, secondMatrixCols);
    setupMatrixFrame(resultMatrixFrame, resultWidgetMatrix, firstMatrixRows, secondMatrixRows);
}

void MultiplyDialog::prepareMultiplyMatrixes()
{
    Matrix *firstMatrix = new Matrix(firstMatrixCols);
    for (int j = 0; j < firstMatrixCols; ++j) {
        (*firstMatrix)[0][j] = (*firstWidgetMatrix)[0][j]->value();
    }

    Matrix *secondMatrix = new Matrix(secondMatrixRows, firstMatrixCols);
    for (int i = 0; i < secondMatrixRows; ++i) {
        for (int j = 0; j < secondMatrixCols; ++j) {
            (*secondMatrix)[i][j] = (*secondWidgetMatrix)[i][j]->value();
        }
    }

    uint8_t resultMatrixRows = 1;
    uint8_t resultMatrixCols = secondMatrixRows;

    Matrix *resultMatrix = new Matrix(1, secondMatrixRows);

    *resultMatrix = (*secondMatrix) * (*firstMatrix);

    for (int i = 0; i < resultMatrixRows; ++i) {
        for (int j = 0; j < resultMatrixCols; ++j) {
            (*resultWidgetMatrix)[i][j]->setValue((*resultMatrix)[i][j]);
        }
    }

    delete firstMatrix;
    delete secondMatrix;
    delete resultMatrix;
}
