#include "mainwindow.h"
#include <QApplication>
#include "fann.h"
#include "floatfann.h"

#define IRIS_DATA_TRAIN_FILE "iris_dataset.train"
#define IRIS_DATA_TEST_FILE "iris_dataset.test"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    // amount of layers (with input and output layers)
    const unsigned int layersNum = 3;
    // amount of hidden neurons
    const unsigned int hiddenNeuronsNum1 = 65;
    // указатель на нашу нейронную сеть.
    struct fann *network;
    // указатели на структуры данных, где будут находится загруженные наборы данных.
    struct fann_train_data *trainData, *testData;
    // указатель для вывода выходных значений выходных нейронов.
    fann_type *output;

    trainData = fann_read_train_from_file(IRIS_DATA_TRAIN_FILE);
    testData = fann_read_train_from_file(IRIS_DATA_TEST_FILE);

    network = fann_create_standard(layersNum, trainData->num_input, hiddenNeuronsNum1, trainData->num_output);


    w.show();

    return a.exec();
}
