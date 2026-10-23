#include "networkscene.h"
#include "commons.h"
#include <QGraphicsSimpleTextItem>

NetworkScene::NetworkScene(QObject *parent)
    : QGraphicsScene {parent}
    //, layers(2)
    , neurons {2,2}
{

}

void NetworkScene::setScene(QList<uint16_t> netDefinition)
{
    uint16_t max = *(std::max_element(netDefinition.begin(), netDefinition.end()));

    uint16_t layers = netDefinition.size();
    static uint16_t wDistance = 50;
    static uint16_t hDistance = 60;
    static uint16_t width = 20;
    static uint16_t height = 40;    
    outputAksonMatrix = new Matrix(layers, max);

    for (uint16_t i = 0; i < layers; ++i) {
        uint16_t elementCount = netDefinition[i];
        for (uint16_t j = 0; j < elementCount; ++j) {
            uint16_t bias = (max - elementCount) * hDistance / 2;
            // synapsy
            addLine(90 + wDistance * i, bias + 100 + hDistance * j, 100 + wDistance * i, bias + 100 + hDistance * j);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + height / 4, 100 + wDistance * i, bias + 100 + hDistance * j + height / 4);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + height / 2, 100 + wDistance * i, bias + 100 + hDistance * j + height / 2);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + 3 * height / 4, 100 + wDistance * i, bias + 100 + hDistance * j + 3 * height / 4);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + height, 100 + wDistance * i, bias + 100 + hDistance * j + height);

            // akson
            uint16_t xAksonEnd = 110 + wDistance * i + width;
            uint16_t yAksonEnd = bias + 100 + hDistance * j + height / 2;
            (*outputAksonMatrix)[i][j];
            addLine(100 + wDistance * i + width, bias + 100 + hDistance * j + height / 2, xAksonEnd, yAksonEnd);

            addRect(100 + wDistance * i, bias + 100 + hDistance * j, 20, 40);
            if (i == layers - 1)  {
                outputValueCoordinates.append(qMakePair(140 + wDistance * i, bias + 100 + hDistance * j));
            }
        }
    }
}

void NetworkScene::showOutput(const Matrix *output)
{
    int count  = 0;
    for (QPair<double, double> p : std::as_const(outputValueCoordinates)) {
        auto *txt =  addSimpleText(QString::number((*output)[0][count]));
        txt->setPos(p.first, p.second);
        ++count;
    }
}


