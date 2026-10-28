#include "network.h"
#include <cassert>
#include <cmath>
#include <QFile>
#include <QMessageBox>

using namespace std;

Network::Network(const uint16_t inputSignals, const QList<uint16_t> &layers, QWidget *parent)
    : parent_(parent)
    , layersCount_(layers.size())
    , inputMatrix(nullptr)
    , outputMatrix(nullptr)
{
    Matrix *matrix = new Matrix(layers[0], inputSignals + 1);
    matrix->setRandomValues();
    matrix->normalization();
    layer_.append(matrix);
    layer_.append(new Matrix(layers[0]));        // warstwa sygnałów wyjściowych z pierwszej warstwy
    for (uint16_t i = 1; i < layersCount_; ++i) {
        matrix = new Matrix(layers[i], layers[i - 1] + 1);
        matrix->setRandomValues();
        matrix->normalization();
        layer_.append(matrix);
        layer_.append(new Matrix(layers[i]));        // warstwa sygnałów wyjściowych z i-tej warstwy
    }
}

Network::~Network()
{
    for (Matrix *m : std::as_const(layer_)) {
        delete m;
    }
}

bool Network::readFile(const string &fileName)
{
    QFile file(QString::fromStdString(fileName));
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Nie można otworzyć pliku " + fileName;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    // Offset danych pikseli (bajty 10–13)
    quint32 pixelDataOffset;
    memcpy(&pixelDataOffset, data.constData() + 10, 4);

    const uchar* pixelData = reinterpret_cast<const uchar*>(data.constData() + pixelDataOffset);

    // BMP zapisuje obraz OD DOŁU
    int counter = 0;
    QList<double> matrixRow;
    for (int y = 19; y >= 0; y--) {
        const uchar* row = pixelData + y * 4;  // 4 bajty na wiersz

        for (int x = 0; x < 20; x++) {
            int byteIndex = x / 8;
            int bitIndex  = 7 - (x % 8);
            bool pixel = (row[byteIndex] >> bitIndex) & 1;
            matrixRow.append(pixel ? 1 : 0);
        }
    }

    inputMatrix = new Matrix(400);
    inputMatrix->setInput(std::move(matrixRow));
    inputMatrix->normalization();
    layer_.push_front(inputMatrix);
    return true;
}

void Network::readFile(const QString &fileName, char &character, const char md)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Nie można otworzyć pliku " + fileName;
        throw QFile::FileError();
    }

    QByteArray data = file.readAll();
    file.close();

    // Offset danych pikseli (bajty 10–13)
    quint32 pixelDataOffset;
    memcpy(&pixelDataOffset, data.constData() + 10, 4);

    const uchar* pixelData = reinterpret_cast<const uchar*>(data.constData() + pixelDataOffset);

    // BMP zapisuje obraz OD DOŁU

    int counter = 0;
    QList<double> matrixRow;
    for (int y = 19; y >= 0; y--) {
        const uchar* row = pixelData + y * 4;  // 4 bajty na wiersz

        for (int x = 0; x < 20; x++) {
            int byteIndex = x / 8;
            int bitIndex  = 7 - (x % 8);
            bool pixel = (row[byteIndex] >> bitIndex) & 1;
            matrixRow.append(pixel ? 1 : 0);
        }
    }

    if (inputMatrix == nullptr) {
        inputMatrix = new Matrix(400);
        inputMatrix->setInput(std::move(matrixRow));
    } else {
        inputMatrix->addInputData(std::move(matrixRow));
    }

    QList<double> outputColumn({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    if (character == 'A' || character == 'a') {
        if (md == 'd')
            outputColumn[0] = 1;
        else if (md == 'm')
            outputColumn[1] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [a]");
    } else if (character == 'B' || character == 'b') {
        if (md == 'd')
            outputColumn[2] = 1;
        else if (md == 'm')
            outputColumn[3] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [b]");
    } else if (character == 'C' || character == 'c') {
        if (md == 'd')
            outputColumn[4] = 1;
        else if (md == 'm')
            outputColumn[5] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [c]");
    } else if (character == 'D' || character == 'd') {
        if (md == 'd')
            outputColumn[6] = 1;
        else if (md == 'm')
            outputColumn[7] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [d]");
    }  else if (character == 'E' || character == 'e') {
        if (md == 'd')
            outputColumn[8] = 1;
        else if (md == 'm')
            outputColumn[9] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [e]");
    } else if (character == 'F' || character == 'f') {
        if (md == 'd')
            outputColumn[10] = 1;
        else if (md == 'm')
            outputColumn[11] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [f]");
    } else if (character == 'G' || character == 'g') {
        if (md == 'd')
            outputColumn[12] = 1;
        else if (md == 'm')
            outputColumn[13] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [g]");
    } else if (character == 'H' || character == 'h') {
        if (md == 'd')
            outputColumn[14] = 1;
        else if (md == 'm')
            outputColumn[15] = 1;
        else
            QMessageBox::critical(parent_, "Error", "Błąd w danych wejściowych [h]");
    }

    if (outputMatrix == nullptr) {
        outputMatrix = new Matrix(16);
        outputMatrix->setInput(outputColumn);
    } else {
        outputMatrix->addInputData(outputColumn);
    }
}

void Network::backPropagation()
{

}

void Network::readLearningSequence()
{
    for (char ch = 'A'; ch <= 'H'; ++ch) {
        for (char n = '1'; n <= '3'; ++n) {
            QString name(ch);
            name += n;
            name += "_d.bmp";
            QString fileName = "..//NNCiag/" + name;
            try {
                readFile(fileName, ch, 'm');
                readFile(fileName, ch, 'd');
            } catch (QFile::FileError &err) {
                QMessageBox::critical(parent_, "FileError","Odczyt pliku z danymi wejściowymi");
            }
        }
    }

    inputMatrix->normalization();
}

void Network::startLearning()
{

}

void Network::goForward()
{
    uint16_t currentLayer = 1;
    uint16_t layerCount = 0;

    while (layerCount < layersCount_) {
        *layer_[currentLayer + 1] = (*layer_[currentLayer]) * (*layer_[currentLayer - 1]);
        layer_[currentLayer + 1]->activation();
        currentLayer += 2;
        ++layerCount;
    }
}

QList<Matrix*> Network::network()
{
    return layer_;
}

// void Network::sigmoid_derivate(Matrix &matrix, const double sigma) // do poprawy
// {
//     //pochodna
//     //-e^x/(1+e^x)^2
//     int row = matrix.size();
//     int col = matrix[0].size();

//     for (int i = 0; i < row; ++i) {
//         for (int j = 0; j < col; ++j) {
//             matrix[i][j] = -sigma*exp(matrix[i][j]) / pow((1.0 + exp(-sigma*matrix[i][j])), 2.0);
//         }
//     }
// }

// Matrix Network::squareActivation(const Matrix &matrix)
// {
//     Matrix ret(matrix.size(), vector<double>(matrix[0].size()));

//     int row = matrix.size();
//     int col = matrix[0].size();

//     for (int i = 0; i < row; ++i) {
//         for (int j = 0; j < col; ++j) {
//             if (matrix[i][j] < 0.0) {
//                 ret[i][j] = -sqrt(abs(matrix[i][j]));
//             } else {
//                 ret[i][j] = sqrt(matrix[i][j]);
//             }
//         }
//     }

//     return ret;
// }

// Matrix Network::quasiLineActivation(const Matrix &matrix, const double x)
// {
//     Matrix ret(matrix.size(), vector<double>(matrix[0].size()));

//     int row = matrix.size();
//     int col = matrix[0].size();

//     for (int i = 0; i < row; ++i) {
//         for (int j = 0; j < col; ++j) {
//             if (matrix[i][j] < 0.0) {
//                 ret[i][j] = 0.1 * matrix[i][j];
//             } else {
//                 ret[i][j] = x * matrix[i][j];
//             }
//         }
//     }

//     return ret;
// }
