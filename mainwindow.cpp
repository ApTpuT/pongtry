#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(LeftShift()));
    //ui->textEdit->insertPlainText(QString::number(ui->plainTextEdit->));
}

void MainWindow::LeftShift()
{
    QString myString = ui->plainTextEdit->toPlainText();

    QStringList sList = myString.split(QLatin1String("\n")); // или \n\r

    ui->plainTextEdit->setPlainText(sList.join("\n"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


