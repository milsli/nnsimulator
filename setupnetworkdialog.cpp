#include "setupnetworkdialog.h"

#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>


SetupNetworkDialog::SetupNetworkDialog(QWidget  *parent, Qt::WindowFlags f)
    : QDialog{parent, f}
    , layersNumber(2)
{
    setupView();
}

uint16_t SetupNetworkDialog::layers(QList<uint16_t> &layers)
{
    uint16_t signalsSize = inputSignals->text().toInt();

    for (int i = 0 ; i < layersNumber; ++i) {
        QTableWidgetItem *item = setupTable->item(i, 0);
        item->data(Qt::EditRole).toInt();
        layers.push_back(item->data(Qt::EditRole).toInt());
    }

    return signalsSize;
}

void SetupNetworkDialog::accept()
{
    QDialog::accept();
}

void SetupNetworkDialog::setLayers(int layers)
{
    layersNumber = layers + 2;
    setupTable->setRowCount(layersNumber);
}

void SetupNetworkDialog::setupView()
{
    inputSignals = new QLineEdit;
    inputSignals->setValidator(new QIntValidator(2, 500));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(new QLabel("Liczba wejść"));
    topLayout->addWidget(inputSignals);

    QStringList items {"2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
    layersNumberCombo = new QComboBox(this);
    layersNumberCombo->addItems(items);
    layersNumberCombo->setCurrentIndex(0);
    connect(layersNumberCombo, &QComboBox::currentIndexChanged, this, &SetupNetworkDialog::setLayers);

    QHBoxLayout *layersLayout = new QHBoxLayout;
    layersLayout->addWidget(new QLabel("Liczba warstw"));
    layersLayout->addWidget(layersNumberCombo);

    setupTable = new QTableWidget(layersNumber, 1, this);
    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addWidget(setupTable);

    acceptButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    connect(acceptButton, &QPushButton::clicked, this, &SetupNetworkDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &SetupNetworkDialog::reject);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(acceptButton);
    bottomLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(layersLayout);
    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}
