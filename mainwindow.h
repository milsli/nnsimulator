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

    void setupNetworkSlot();
    void transposeMatrixSlot();
    void multiplyMatrixSlot();

    void showValues();

private:    
    void setupView();
    void setupMenu();

private:

//  *** menu ***
    QMenu *networkMenu;
    QAction *setupNetworkAction;
    QMenu *matrixMenu;
    QAction *transposeMatrixAction;
    QAction *multiplyMatrixAction;
// *** menu ***

// *** Network View ***
    NetworkScene * networkScene_;
    NetworkView * networkView;
// *** Network View ***

    QPushButton *startLerningButton;
    QPushButton *showInterior;
    QLineEdit *messagesBox;
    Network *network_;
};
#endif // MAINWINDOW_H
