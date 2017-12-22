#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include "qDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    typecont=false;
    lastval=0;
    way=1;
    curline=4;
    curpos=40;
    plapos=22;
    learnRate = 0.5;
    int l=1;
    int r=2;
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(LShift()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(RShift()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(IIC()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(Create()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(TimeStop()));
    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(150); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime())); // Подключаем сигнал таймера к нашему слоту
    initWeights << 0.001<< 0.002<< 0.003<<
                   0.005<< 0.006<< 0.007<<
                   0.009<< 0.010<< 0.011<<

                   0.013<< 0.014<< 0.015<<

                   0.017<< 0.018<<
                   0.019<< 0.020<<
                   0.021<< 0.022<<
                   0.023<< 0.024<<

                   0.025<< 0.026;
    finalWeights=initWeights;

    tmr->start(); // Запускаем таймер



}

void MainWindow::TimeStop()
{
    if (tmr->isActive())tmr->stop();
    else  tmr->start();
}

void MainWindow::IIC()
{
    if (typecont==false) typecont=true;
    else typecont=false;
}

void MainWindow::Create()
{
    ui->plainTextEdit_2->insertPlainText("\nBegin Neural Network training using Back-Propagation demo\n");

    //"\nBegin Neural Network training using Back-Propagation demo\n";

    //Random rnd = new Random(1); // for random weights. not used.
    Helpers Helper;
    QList <double> xValues;
    xValues<< 40.0 << 4.0 << 22.0 ; // inputs
    QList <double> yValues; // outputs
    QList <double> tValues;
    tValues <<1; // target values

    //qDebug() <<("The fixed input xValues are:");
    Helper.ShowVector(xValues, 1, 8, true);

    //qDebug() <<"The fixed target tValues are:";
    Helper.ShowVector(tValues, 4, 8, true);

    int numInput = 3;
    int numHidden = 9;
    int numOutput = 1;
    int numWeights = (numInput * numHidden) + (numHidden * numOutput) + (numHidden + numOutput);

    ui->plainTextEdit_2->insertPlainText("Creating a " + QString::number(numInput) + "-input, " + QString::number(numHidden) + "-hidden, " + QString::number(numOutput) + "-output neural network\n");
    ui->plainTextEdit_2->insertPlainText("Using hard-coded tanh function for hidden layer activation\n");
   ui->plainTextEdit_2->insertPlainText("Using hard-coded log-sigmoid function for output layer activation\n");

    BackPropNeuralNet bnn = BackPropNeuralNet(numInput, numHidden, numOutput);

    ////qDebug() <<"\nGenerating random initial weights and bias values");
    //double[] initWeights = new double[numWeights];
    //for (int i = 0; i < initWeights.Length; ++i)
    //  initWeights[i] = (0.1 - 0.01) * rnd.NextDouble() + 0.01;

   ui->plainTextEdit_2->insertPlainText("\nCreating arbitrary initial weights and bias values\n");


   ui->plainTextEdit_2->insertPlainText("\nInitial weights and biases are:\n");
    Helper.ShowVector(initWeights, 3, 8, true);

    ui->plainTextEdit_2->insertPlainText("Loading neural network initial weights and biases into neural network\n");
    bnn.SetWeights(initWeights);

    learnRate = 2;  // learning rate - controls the maginitude of the increase in the change in weights.
    double momentum = 0.1; // momentum - to discourage oscillation.
   ui->plainTextEdit_2->insertPlainText("Setting learning rate = " + QString::number(learnRate) + " and momentum = " + QString::number(momentum)+"\n");

    int maxEpochs = 10000;
    double errorThresh = 0.001;
   ui->plainTextEdit_2->insertPlainText("\nSetting max epochs = " + QString::number(maxEpochs) + " and error threshold = " + QString::number(errorThresh)+"\n");

    int epoch = 0;
    double error = std::numeric_limits<qreal>::max();
    ui->plainTextEdit_2->insertPlainText("\nBeginning training using back-propagation\n");

    while (epoch < maxEpochs) // train
    {
      if (epoch % 20 == 0)  ui->plainTextEdit_2->insertPlainText("epoch = " + QString::number(epoch)+"\n");

      yValues = bnn.ComputeOutputs(xValues);
      error = Helper.Error(tValues, yValues);
      if (error < errorThresh)
      {
        ui->plainTextEdit_2->insertPlainText("Found weights and bias values that meet the error criterion at epoch " + QString::number(epoch)+"\n");
        break;
      }
      bnn.UpdateWeights(tValues, learnRate, learnRate);
      ++epoch;
    } // train loop

    finalWeights = bnn.GetWeights();
    ui->plainTextEdit_2->insertPlainText( "");
    ui->plainTextEdit_2->insertPlainText("Final neural network weights and bias values are:");
    Helper.ShowVector(finalWeights, 5, 8, true);

    yValues = bnn.ComputeOutputs(xValues);
    ui->plainTextEdit_2->insertPlainText("\nThe yValues using final weights are:");
    Helper.ShowVector(yValues, 8, 8, true);

    double finalError = Helper.Error(tValues, yValues);
    ui->plainTextEdit_2->insertPlainText("\nThe final error is " + QString::number(finalError));

    ui->plainTextEdit_2->insertPlainText("\nEnd Neural Network Back-Propagation demo\n");

} // Program


void MainWindow::LShift()
{
    if (plapos>2 && plapos<52){
    QString myString = ui->plainTextEdit->toPlainText();
    QStringList sList = myString.split(QLatin1String("\n"));
    sList[16].remove(1,1);
    plapos--;
    sList[16].insert(50,QString(" "));
    ui->plainTextEdit->setPlainText(sList.join("\n"));
    lastval=-1;
    }
}


void MainWindow::RShift()
{
    if (plapos>0 && plapos<43){
    QString myString = ui->plainTextEdit->toPlainText();
    QStringList sList = myString.split(QLatin1String("\n"));
    sList[16].remove(50,1);
    plapos++;
    sList[16].insert(1,QString(" "));
    ui->plainTextEdit->setPlainText(sList.join("\n"));
    lastval=2;
    }
}

void MainWindow::updateTime()
{
    BallCheck();
    BallMove();
    double error = std::numeric_limits<qreal>::max();

    QList <double> xValues;
    QList <double> yValues;
    QList <double> tValues;
    double errorThresh = 0.00001;
    bnn.SetWeights(finalWeights);
    xValues<< curpos << curline << plapos ;
    yValues = bnn.ComputeOutputs(xValues);
    tValues <<lastval; // target values
    error = Helper.Error(tValues, yValues);
    qDebug()<<tValues<<" "<< yValues <<" "<<xValues <<endl;

    if (error < errorThresh)
    {
      ui->plainTextEdit_2->insertPlainText("Found weights and bias values that meet the error criterion at epoch ");
    }
    bnn.UpdateWeights(tValues, learnRate, learnRate);
    if (typecont==true){
    if (yValues[0]>1) RShift();
    else LShift();
   }
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


