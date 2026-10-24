#include "networkscene.h"
#include <QGraphicsSimpleTextItem>

NetworkScene::NetworkScene(QObject *parent)
    : QGraphicsScene {parent}
    , layers_(2)
    , maxNeuronsInLayer_(2)
{

}

void NetworkScene::setScene(const QList<uint16_t> &netDefinition)
{
    netDefinition_ = netDefinition;
    layers_ = netDefinition_.size();
    maxNeuronsInLayer_ = *(std::max_element(netDefinition_.begin(), netDefinition_.end()));

    static uint16_t wDistance = 80;
    static uint16_t hDistance = 60;
    static uint16_t width = 20;
    static uint16_t height = 40;
    outputAksonMatrix = new MatrixTemplate<QPair<int, int>>(layers_, maxNeuronsInLayer_);

    for (uint16_t i = 0; i < layers_; ++i) {
        uint16_t elementCount = netDefinition_[i];
        for (uint16_t j = 0; j < elementCount; ++j) {
            uint16_t bias = (maxNeuronsInLayer_ - elementCount) * hDistance / 2;
            // synapsy
            addLine(90 + wDistance * i, bias + 100 + hDistance * j, 100 + wDistance * i, bias + 100 + hDistance * j);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + height / 4, 100 + wDistance * i, bias + 100 + hDistance * j + height / 4);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + height / 2, 100 + wDistance * i, bias + 100 + hDistance * j + height / 2);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + 3 * height / 4, 100 + wDistance * i, bias + 100 + hDistance * j + 3 * height / 4);
            addLine(90 + wDistance * i, bias + 100 + hDistance * j + height, 100 + wDistance * i, bias + 100 + hDistance * j + height);

            // akson
            uint16_t xAksonEnd = 110 + wDistance * i + width;
            uint16_t yAksonEnd = bias + 100 + hDistance * j + height / 2;
            (*outputAksonMatrix)[i][j] = qMakePair(xAksonEnd, yAksonEnd);
            addLine(100 + wDistance * i + width, bias + 100 + hDistance * j + height / 2, xAksonEnd, yAksonEnd);

            addRect(100 + wDistance * i, bias + 100 + hDistance * j, 20, 40);
            if (i == layers_ - 1)  {
                outputValueCoordinates.append(qMakePair(140 + wDistance * i, bias + 100 + hDistance * j));
            }
        }
    }
}

void NetworkScene::showOutput(const QList<Matrix *>& network)
{
    uint16_t layerIndex = 2;
    for (int i = 0; i < layers_; ++i) {
        uint16_t elementCount = netDefinition_[i];
        Matrix *mat = network[layerIndex];
        for (uint16_t j = 0; j < elementCount; ++j) {
            QPair<int, int> point = (*outputAksonMatrix)[i][j];
            double var = (*mat)[0][j];
            auto *txt =  addSimpleText(QString::number(var));
            txt->setPos(point.first + 2, point.second - 8);
        }
        layerIndex += 2;
    }
}


