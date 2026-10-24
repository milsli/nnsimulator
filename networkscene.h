#ifndef NETWORKSCENE_H
#define NETWORKSCENE_H

#include <QGraphicsScene>
#include "commons.h"


class NetworkScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NetworkScene(QObject *parent = nullptr);

    void setScene(const QList<uint16_t>& netDefinition);
    void showOutput(const QList<Matrix *> &network);

private:
    QList<QPair<double, double>> outputValueCoordinates;

private:
    uint16_t layers_;
    uint16_t maxNeuronsInLayer_;
    MatrixTemplate<QPair<int, int>> *outputAksonMatrix;
    QList<uint16_t> netDefinition_;

signals:
};

#endif // NETWORKSCENE_H
