#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

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


    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void BallMove();
    void BallCheck();
    void changedir(int wall);


private slots:
 void RShift();
 void LShift();
  void updateTime();
};

#endif // MAINWINDOW_H
