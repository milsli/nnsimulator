#include "showvaluesdialog.h"
#include "network.h"
#include <QScrollArea>
#include <QVBoxLayout>

ShowValuesDialog::ShowValuesDialog(Network* const network,QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
    network_ = network;
}

void ShowValuesDialog::setupView()
{
    showArea_ = new QScrollArea;
    QVBoxLayout *mainLayout = new QVBoxLayout;


    mainLayout->addWidget(showArea_);

    setLayout(mainLayout);
}
