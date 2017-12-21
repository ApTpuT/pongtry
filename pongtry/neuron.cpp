#include<QApplication>
#include"neuron.h"
#include"helpers.h"
#include"net.h"

BackPropProgram::BackPropProgram()
{

}


void BackPropProgram::Create()
{
    qDebug() << "\nBegin Neural Network training using Back-Propagation demo\n";

    //Random rnd = new Random(1); // for random weights. not used.
    Helpers Helper;
    QList <double> xValues;
    xValues<< 1.0 << -2.0 << 3.0 ; // inputs
    QList <double> yValues; // outputs
    QList <double> tValues;
    tValues <<0.1234 << 0.8766; // target values

    qDebug() <<("The fixed input xValues are:");
    Helper.ShowVector(xValues, 1, 8, true);

    qDebug() <<"The fixed target tValues are:";
    Helper.ShowVector(tValues, 4, 8, true);

    int numInput = 3;
    int numHidden = 4;
    int numOutput = 2;
    int numWeights = (numInput * numHidden) + (numHidden * numOutput) + (numHidden + numOutput);

    qDebug() <<"Creating a " << numInput << "-input, " << numHidden << "-hidden, " << numOutput << "-output neural network";
    qDebug() <<"Using hard-coded tanh function for hidden layer activation";
    qDebug() <<"Using hard-coded log-sigmoid function for output layer activation";

    BackPropNeuralNet bnn = BackPropNeuralNet(numInput, numHidden, numOutput);

    //qDebug() <<"\nGenerating random initial weights and bias values");
    //double[] initWeights = new double[numWeights];
    //for (int i = 0; i < initWeights.Length; ++i)
    //  initWeights[i] = (0.1 - 0.01) * rnd.NextDouble() + 0.01;

    qDebug() <<"\nCreating arbitrary initial weights and bias values";
    QList <double> initWeights;
    initWeights << 0.001<< 0.002<< 0.003<< 0.004<<
                   0.005<< 0.006<< 0.007<< 0.008<<
                   0.009<< 0.010<< 0.011<< 0.012<<

                   0.013<< 0.014<< 0.015<< 0.016<<

                   0.017<< 0.018<<
                   0.019<< 0.020<<
                   0.021<< 0.022<<
                   0.023<< 0.024<<

                   0.025<< 0.026;

    qDebug() <<"\nInitial weights and biases are:";
    Helper.ShowVector(initWeights, 3, 8, true);

    qDebug() <<"Loading neural network initial weights and biases into neural network";
    bnn.SetWeights(initWeights);

    double learnRate = 0.5;  // learning rate - controls the maginitude of the increase in the change in weights.
    double momentum = 0.1; // momentum - to discourage oscillation.
   qDebug() << "Setting learning rate = " << QString::number(learnRate) << " and momentum = " << QString::number(momentum);

    int maxEpochs = 10000;
    double errorThresh = 0.0001;
    qDebug() << "\nSetting max epochs = " << maxEpochs << " and error threshold = " << QString::number(errorThresh);

    int epoch = 0;
    double error = std::numeric_limits<qreal>::max();
    qDebug() <<"\nBeginning training using back-propagation\n";

    while (epoch < maxEpochs) // train
    {
      if (epoch % 20 == 0) qDebug() << "epoch = " << epoch;

      yValues = bnn.ComputeOutputs(xValues);
      error = Helper.Error(tValues, yValues);
      if (error < errorThresh)
      {
        qDebug() <<"Found weights and bias values that meet the error criterion at epoch " << epoch;
        break;
      }
      bnn.UpdateWeights(tValues, learnRate, learnRate);
      ++epoch;
    } // train loop

    QList <double> finalWeights = bnn.GetWeights();
    qDebug() << "";
    qDebug() << "Final neural network weights and bias values are:";
    Helper.ShowVector(finalWeights, 5, 8, true);

    yValues = bnn.ComputeOutputs(xValues);
    qDebug() <<"\nThe yValues using final weights are:";
    Helper.ShowVector(yValues, 8, 8, true);

    double finalError = Helper.Error(tValues, yValues);
    qDebug() << "\nThe final error is " << QString::number(finalError);

    qDebug() <<"\nEnd Neural Network Back-Propagation demo\n";
}; // Program
