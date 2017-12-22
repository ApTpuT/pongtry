#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QApplication>
#include <mainwindow.h>
#include"helpers.h"
#include"net.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    QTimer *tmr;
    int way;
    int curline;
     int curpos;
    double learnRate;
   int plapos;
    bool typecont;
    int lastval;
    QList <double> initWeights;
    QList <double> finalWeights;
    Helpers Helper;
    BackPropNeuralNet bnn=BackPropNeuralNet(3, 4, 1);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void BallMove();
    void BallCheck();
    void changedir(int wall);


private slots:

    void TimeStop();
    void Create();
 void RShift();
 void LShift();
  void updateTime();
  void IIC();
};

#endif // MAINWINDOW_H
