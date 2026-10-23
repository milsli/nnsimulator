#ifndef SETUPNETWORKDIALOG_H
#define SETUPNETWORKDIALOG_H

#include <QDialog>


class QComboBox;
class QPushButton;
class QTableWidget;
class QLineEdit;

class SetupNetworkDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetupNetworkDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    uint16_t layers(QList<uint16_t> &layers);

public slots:
    void accept();

private slots:
    void setLayers(int layers);


private:

    void setupView();


private:
    QLineEdit *inputSignals;
    QComboBox *layersNumberCombo;
    QTableWidget *setupTable;
    uint16_t layersNumber;
    QPushButton *acceptButton;
    QPushButton *cancelButton;

signals:

};

#endif // SETUPNETWORKDIALOG_H
