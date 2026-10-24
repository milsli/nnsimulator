#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include "commons.h"


class Network
{
public:
    Network(const uint16_t inputSignals, const QList<uint16_t> &layers);
    ~Network();

    bool readFile(const std::string &fileName, char character, const char md);
    void backPropagation();

public:

    // Matrix sigmoidActivation(const Matrix &matrix, const double sigma = 0.5);
    // void sigmoid_derivate(Matrix &matrix, const double sigma);
    // Matrix squareActivation(const Matrix &matrix);
    // Matrix quasiLineActivation(const Matrix &matrix, const double x = 0.5);


    //Matrix

    void goForward();
    QList<Matrix *> network();

private:
    uint16_t layersCount_;
    Matrix *inputMatrix;

    // definicja całej sieci
    QList<Matrix*> layer_;

    // train sequence
    //std::vector<Matrix> inputSignals;  // train x sequence in inputSignals[0] w sumie elementów tyle co warstw
    //Matrix outputSignals; // y

    // hidden layer structure
    //std::vector<Matrix> hiddenLayerWages;       // elementów tyle co warstw - 1

    // output layer structure
    //Matrix outputLayerOutput;

    // std::vector<unsigned int> hiddenLayerSize;


};

#endif // NETWORK_H
