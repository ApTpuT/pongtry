#ifndef NET_H
#define NET_H
#include"helpers.h"

class BackPropNeuralNet
{
public:
    BackPropNeuralNet(int numInput, int numHidden, int numOutput);
    void SetWeights(QList <double> weights);
    QList <double> GetWeights();
    QList <double> GetOutputs();
    QList <double> ComputeOutputs(QList <double> xValues);
    void UpdateWeights(QList <double> tValues, double learn, double mom); // back-propagation

private:
        int numInput;
        int numHidden;
        int numOutput;

        QList <double> inputs;
        QList <QList<double>> ihWeights; // input-to-hidden
        QList <double> hBiases;
        QList <double> hSums;
        QList <double> hOutputs;

        QList <QList<double>> hoWeights;  // hidden-to-output
        QList <double> oBiases;
        QList <double> oSums;
        QList <double> outputs;

        //private string hActivation; // "log-sigmoid" or "tanh"
        //private string oActivation; // "log-sigmoid" or "tanh"

        QList <double> oGrads; // output gradients for back-propagation
        QList <double> hGrads; // hidden gradients for back-propagation

        QList <QList<double>> ihPrevWeightsDelta;  // for momentum with back-propagation
        QList <double> hPrevBiasesDelta;
        QList <QList<double>> hoPrevWeightsDelta;
        QList <double> oPrevBiasesDelta;
        static double SigmoidFunction(double x)
        {
          if (x < -45.0) return 0.0;
          else if (x > 45.0) return 1.0;
          else return 1.0 / (1.0 + exp(-x));
        }

       static double HyperTanFunction(double x)
        {
          if (x < -45.0) return -1.0;
          else if (x > 45.0) return 1.0;
          else return tanh(x);
        }




};

#endif // NET_H
