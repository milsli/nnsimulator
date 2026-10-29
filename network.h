#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include "commons.h"


class Network
{
public:
    Network(const uint16_t inputSignals, const QList<uint16_t> &layers, QWidget *parent);
    ~Network();

    bool readFile(const std::string &fileName);
    void readFile(const QString &fileName, char &character, const char md);
    void backPropagation();
    void readLearningSequence();
    void startLearning();

public:

    // void sigmoid_derivate(Matrix &matrix, const double sigma);
    // Matrix squareActivation(const Matrix &matrix);
    // Matrix quasiLineActivation(const Matrix &matrix, const double x = 0.5);

    void goForward();
    QList<Matrix *> network();

private:
    QWidget *parent_;
    uint16_t inputSignals_;
    uint16_t layersCount_;
    Matrix *inputMatrix;
    Matrix *outputMatrix;

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
