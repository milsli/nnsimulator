#ifndef SHOWVALUESDIALOG_H
#define SHOWVALUESDIALOG_H

#include <QDialog>

class Network;
class QScrollArea;

class ShowValuesDialog : public QDialog
{
    Q_OBJECT
public:
    ShowValuesDialog(Network * const network = nullptr, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    void setupView();

private:
    QScrollArea *showArea_;
    Network *network_;
};

#endif // SHOWVALUESDIALOG_H
