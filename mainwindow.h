#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableWidget;
class QPushButton;
class QLineEdit;
class Network;
class QMenu;
class QAction;
class NetworkView;
class NetworkScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void startLearning();
    void readFiles();

    void setupNetworkSlot();
    void transposeMatrixSlot();
    void multiplyMatrixSlot();

private:    
    void setupView();
    void setupMenu();



private:
    //view
    // QTableWidget *inputTable;
    // QTableWidget *outputTable;


//  *** menu ***
    QMenu *networkMenu;
    QAction *setupNetworkAction;
    QMenu *matrixMenu;
    QAction *transposeMatrixAction;
    QAction *multiplyMatrixAction;
// *** menu ***

// *** Network View ***
    NetworkScene * networkScene;
    NetworkView * networkView;
// *** Network View ***


    QPushButton *startLerningButton;
    QPushButton *readFilesButton;

    QLineEdit *messagesBox;

    Network *network;



};
#endif // MAINWINDOW_H
