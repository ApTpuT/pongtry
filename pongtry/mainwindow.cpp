#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    way=3;
    curline=4;
    curpos=40;
    int l=1;
    int r=2;
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(LShift()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(RShift()));
    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(150); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime())); // Подключаем сигнал таймера к нашему слоту
    tmr->start(); // Запускаем таймер

}

void MainWindow::LShift()
{

    QString myString = ui->plainTextEdit->toPlainText();
    QStringList sList = myString.split(QLatin1String("\n"));
    sList[16].remove(1,1);
    sList[16].insert(50,QString(" "));
    ui->plainTextEdit->setPlainText(sList.join("\n"));
}


void MainWindow::RShift()
{

    QString myString = ui->plainTextEdit->toPlainText();
    QStringList sList = myString.split(QLatin1String("\n"));
    sList[16].remove(50,1);
    sList[16].insert(1,QString(" "));
    ui->plainTextEdit->setPlainText(sList.join("\n"));
}

void MainWindow::updateTime()
{
    BallCheck();
    BallMove();


}

void MainWindow::BallCheck()
{
    if (curline-1==0) changedir(2);
    if (curpos+1==51) changedir(3);
    if (curpos-1==0) changedir(1);
    if (curline==15)
    {
        QString myString = ui->plainTextEdit->toPlainText();
        QStringList sList = myString.split(QLatin1String("\n"));
        if (sList[curline+1][curpos]=="T"[0]) changedir(4);
    }
}

void MainWindow::BallMove()
{
    if (curline==16) tmr->stop();
    QString myString = ui->plainTextEdit->toPlainText();
    QStringList sList = myString.split(QLatin1String("\n"));
    switch (way)
     {
     case 0:
        {
        sList[curline].replace(curpos,1," ");
        curpos=curpos-1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
        break;
        }
     case 1:
        {
        sList[curline].replace(curpos,1," ");
        curpos=curpos-1;
        curline=curline-1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
        break;
        }
    case 2:
       {
        sList[curline].replace(curpos,1," ");
        curline=curline-1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
       break;
       }
    case 3:
       {
        sList[curline].replace(curpos,1," ");
        curpos=curpos+1;
        curline=curline-1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
       break;
       }
    case 4:
       {
        sList[curline].replace(curpos,1," ");
        curpos=curpos+1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
       break;
       }
    case 5:
       {
       sList[curline].replace(curpos,1," ");
       curpos=curpos+1;
       curline=curline+1;
       sList[curline].replace(curpos,1,"O");
       ui->plainTextEdit->setPlainText(sList.join("\n"));
       break;
       }
    case 6:
       {
        sList[curline].replace(curpos,1," ");
        curline=curline+1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
       break;
       }
    case 7:
       {
        sList[curline].replace(curpos,1," ");
        curpos=curpos-1;
        curline=curline+1;
        sList[curline].replace(curpos,1,"O");
        ui->plainTextEdit->setPlainText(sList.join("\n"));
        break;
       break;
       }


     }
}

void MainWindow::changedir(int wall)
{

    switch (wall)
     {
    case 4:
       {
       if (way==7) way=1;
       if (way==6) way=1;
       if (way==5) way=3;
       break;
       }
     case 3:
        {
        if (way==3) way=1;
        if (way==4) way=7;
        if (way==5) way=7;
        break;
        }
     case 2:
        {
        if (way==1) way=7;
        if (way==2) way=7;
        if (way==3) way=5;
        break;
        }
     case 1:
       {
        if (way==1) way=3;
        if (way==0) way=5;
        if (way==7) way=5;
       break;
       }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


