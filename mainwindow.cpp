#include "mainwindow.h"
#include "network.h"
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QGuiApplication>
#include <QScreen>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "setupnetworkdialog.h"
#include "transposedialog.h"
#include "multiplydialog.h"
#include "networkview.h"
#include "networkscene.h"

using namespace std::chrono_literals;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setupView();

}

MainWindow::~MainWindow() {
    delete network_;
}

void MainWindow::startLearning()
{
    network_->startLearning();
    networkScene_->showOutput(network_->network());
}

void MainWindow::readFiles()
{
//    n = new Network(4, {4, 5, 3});

//    n->prepareTestData();

    // char buffer[10];
    // string directory = "../NNCiag/";
    // string filename;

    // for (char ch = 'A'; ch <= 'Z'; ++ch) {
    //     for (char count = 1; count <= 3; ++count) {
    //         filename = ch + string(itoa(count, buffer, 10)) + "_d.bmp";
    //         n->readFile(directory + filename, ch, 'd');

    //         filename[3] = 'm';
    //         n->readFile(directory + filename, ch, 'm');
    //     }
    // }
    qDebug() << "Wczytane";

//    n->randomSettings();
}

void MainWindow::setupNetworkSlot()
{
    SetupNetworkDialog *dialog = new SetupNetworkDialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        QList<uint16_t> layers;
        uint16_t inputSignals = dialog->layers(layers);
        networkScene_->clear();
        networkScene_->setScene(layers);
        network_ = new Network(inputSignals, layers, this);

        //////////////////////////
        /// testowanie

        // if (network->readFile("..//NNCiag/A1_d.bmp") == true) {
        //     network->goForward();
        //     networkScene->showOutput(network->network());
        // }

        network_->readLearningSequence();

        /////////////////////////
    }
}

void MainWindow::transposeMatrixSlot()
{
    TransposeDialog *dialog = new TransposeDialog(this);
    dialog->exec();
}

void MainWindow::multiplyMatrixSlot()
{
    MultiplyDialog *dialog = new MultiplyDialog(this);
    dialog->exec();
}

void MainWindow::setupView()
{
    QSize windowSize = QGuiApplication::primaryScreen()->availableGeometry().size() * 0.4;
    windowSize.setHeight(windowSize.height() / 2);
    resize(windowSize);

    setupMenu();


    startLerningButton = new QPushButton("Start learning");
    readFilesButton = new QPushButton("Read sequence");


    networkScene_ = new NetworkScene(this);
    networkScene_->setScene({2,2});
    networkView = new NetworkView(this);
    networkView->setScene(networkScene_);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(readFilesButton);
    mainLayout->addWidget(startLerningButton);


    QVBoxLayout *superLayout = new QVBoxLayout;

    superLayout->addWidget(networkView);
    superLayout->addLayout(mainLayout);

    messagesBox = new QLineEdit;
    superLayout->addWidget(messagesBox);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(superLayout);

    setCentralWidget(mainWidget);
    connect(startLerningButton, &QPushButton::clicked, this, &MainWindow::startLearning);
    connect(readFilesButton, &QPushButton::clicked, this, &MainWindow::readFiles);
}

void MainWindow::setupMenu()
{    
    networkMenu = new QMenu("Network", this);
    setupNetworkAction = new QAction("Setup", this);
    networkMenu->addAction(setupNetworkAction);
    connect(setupNetworkAction, &QAction::triggered, this, &MainWindow::setupNetworkSlot);

    matrixMenu = new QMenu("Matrix", this);
    transposeMatrixAction = new QAction("Transposition", this);
    multiplyMatrixAction = new QAction("Multiply", this);
    matrixMenu->addAction(transposeMatrixAction);
    matrixMenu->addAction(multiplyMatrixAction);
    connect(transposeMatrixAction, &QAction::triggered, this, &MainWindow::transposeMatrixSlot);
    connect(multiplyMatrixAction, &QAction::triggered, this, &MainWindow::multiplyMatrixSlot);

    menuBar()->addMenu(networkMenu);
    menuBar()->addMenu(matrixMenu);
}

