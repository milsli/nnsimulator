#ifndef NETWORKSCENE_H
#define NETWORKSCENE_H

#include <QGraphicsScene>
#include "commons.h"


class NetworkScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NetworkScene(QObject *parent = nullptr);

    void setScene(QList<uint16_t> netDefinition);
    void showOutput(const Matrix *output);

private:
    QList<QPair<double, double>> outputValueCoordinates;

private:
    // uint16_t layers;
    QList<uint16_t> neurons;
    Matrix *outputAksonMatrix;

signals:
};

#endif // NETWORKSCENE_H
