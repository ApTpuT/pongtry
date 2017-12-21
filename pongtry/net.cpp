#include "net.h"
#include<QApplication>
#include<QDebug>

BackPropNeuralNet::BackPropNeuralNet(int numInput, int numHidden, int numOutput)
{
  this->numInput = numInput;
  this->numHidden = numHidden;
  this->numOutput = numOutput;
  Helpers Helper;
  for (int i=0; i<numInput; i++) inputs.append(0);
  for (int i=0; i<numHidden; i++)
  {
      hGrads.append(0);
      hBiases.append(0);
      hSums.append(0);
      hOutputs.append(0);
      hPrevBiasesDelta.append(0);
  }
for (int i=0; i<numOutput; i++)
  {
              oBiases.append(0);
              oSums.append(0);
              outputs.append(0);
              oGrads.append(0);
              oPrevBiasesDelta.append(0);
   }


  ihWeights = Helper.MakeMatrix(numInput, numHidden);
  qDebug() <<ihWeights[0].size();
  hoWeights = Helper.MakeMatrix(numHidden, numOutput);
  qDebug() <<hoWeights[0].size();
  ihPrevWeightsDelta = Helper.MakeMatrix(numInput, numHidden);
  hoPrevWeightsDelta = Helper.MakeMatrix(numHidden, numOutput);
}

void BackPropNeuralNet::SetWeights(QList <double> weights)
{
  // assumes weights[] has order: input-to-hidden wts, hidden biases, hidden-to-output wts, output biases
  int numWeights = (numInput * numHidden) + (numHidden * numOutput) + numHidden + numOutput;
  if (weights.length() != numWeights)
   qDebug()<<"The weights array length: " << weights.length() <<
      " does not match the total number of weights and biases: " << numWeights;

  int k = 0; // points into weights param

  for (int i = 0; i < numInput; ++i)
    for (int j = 0; j < numHidden; ++j){
      ihWeights[i][j] = weights[k++];
      qDebug()<<ihWeights[i][j];
    }


  for (int i = 0; i < numHidden; ++i)
    hBiases[i] = weights[k++];

  for (int i = 0; i < numHidden; ++i)
    for (int j = 0; j < numOutput; ++j)
      hoWeights[i][j] = weights[k++];

  for (int i = 0; i < numOutput; ++i)
    oBiases[i]= weights[k++];
}

QList <double> BackPropNeuralNet::GetWeights()
{
  int numWeights = (numInput * numHidden) + (numHidden * numOutput) + numHidden + numOutput;
  QList <double> result;
  int k = 0;
  for (int i = 0; i < ihWeights.length(); ++i)
    for (int j = 0; j < ihWeights[0].length()/numInput; ++j){
      qDebug() <<ihWeights[0].length();
      result << ihWeights[i][j];

    }
  for (int i = 0; i < hBiases.length(); ++i)
    result << hBiases[i];
  for (int i = 0; i < hoWeights.length(); ++i)
    for (int j = 0; j < hoWeights[0].length()/numHidden; ++j)
      result << hoWeights[i][j];
  for (int i = 0; i < oBiases.length(); ++i)
    result << oBiases[i];
  return result;
}

QList <double> BackPropNeuralNet::GetOutputs()
{
  QList <double> result;
  result=this->outputs;
  return result;
}

QList <double> BackPropNeuralNet::ComputeOutputs(QList <double> xValues)
{
  if (xValues.length() != numInput)
    qDebug() << "Inputs array length " << inputs.length() << " does not match NN numInput value " << numInput;

  for (int i = 0; i < numHidden; ++i)
    hSums[i] = 0.0;
  for (int i = 0; i < numOutput; ++i)
    oSums[i] = 0.0;

  for (int i = 0; i < xValues.length(); ++i) // copy x-values to inputs
    this->inputs[i] = xValues[i];

  for (int j = 0; j < numHidden; ++j)  // compute hidden layer weighted sums
    for (int i = 0; i < numInput; ++i)
      hSums[j] += this->inputs[i] * ihWeights[i][j];

  for (int i = 0; i < numHidden; ++i)  // add biases to hidden sums
    hSums[i] += hBiases[i];

  for (int i = 0; i < numHidden; ++i)   // apply tanh activation
    hOutputs[i]=HyperTanFunction(hSums[i]);

  for (int j = 0; j < numOutput; ++j)   // compute output layer weighted sums
    for (int i = 0; i < numHidden; ++i)
      oSums[j] += hOutputs[i] * hoWeights[i][j];

  for (int i = 0; i < numOutput; ++i)  // add biases to output sums
    oSums[i] += oBiases[i];

  for (int i = 0; i < numOutput; ++i)   // apply log-sigmoid activation
    this->outputs[i]= SigmoidFunction(oSums[i]);

 QList <double> result; // for convenience when calling method
  result=this->outputs;
  return result;
} // ComputeOutputs

void BackPropNeuralNet::UpdateWeights(QList <double> tValues, double learn, double mom) // back-propagation
{
  // assumes that SetWeights and ComputeOutputs have been called and so inputs and outputs have values
  if (tValues.length() != numOutput)
    qDebug() <<"target values not same Length as output in UpdateWeights";

  // 1. compute output gradients. assumes log-sigmoid!
  for (int i = 0; i < oGrads.length(); ++i)
  {
    double derivative = (1 - outputs[i]) * outputs[i]; // derivative of log-sigmoid is y(1-y)
    oGrads[i] = derivative * (tValues[i] - outputs[i]); // oGrad = (1 - O)(O) * (T-O)
  }

  // 2. compute hidden gradients. assumes tanh!
  for (int i = 0; i < hGrads.length(); ++i)
  {
    double derivative = (1 - hOutputs[i]) * (1 + hOutputs[i]); // derivative of tanh is (1-y)(1+y)
    double sum = 0.0;
    for (int j = 0; j < numOutput; ++j) // each hidden delta is the sum of numOutput terms
      sum += oGrads[j] * hoWeights[i][j]; // each downstream gradient * outgoing weight
    hGrads[i] = derivative * sum; // hGrad = (1-O)(1+O) * E(oGrads*oWts)
  }
    //qDebug() <<ihWeights.length();
  // 3. update input to hidden weights (gradients must be computed right-to-left but weights can be updated in any order)
  for (int i = 0; i < ihWeights.length(); ++i) // 0..2 (3)
  {

    for (int j = 0; j < ihWeights[0].length()/numInput; ++j) // 0..3 (4)
    {
      double delta = learn * hGrads[j] * inputs[i]; // compute the new delta = "eta * hGrad * input"
      //qDebug() <<ihWeights[0].length();
      ihWeights[i][j] += delta; // update
      ihWeights[i][j] += mom * ihPrevWeightsDelta[i][j]; // add momentum using previous delta. on first pass old value will be 0.0 but that's OK.
      ihPrevWeightsDelta[i][j] = delta; // save the delta for next time
    }
  }

  // 4. update hidden biases
  for (int i = 0; i <hBiases.length(); ++i)
  {
    double delta = learn * hGrads[i] * 1.0; // the 1.0 is the constant input for any bias; could leave out
    hBiases[i] += delta;
    hBiases[i] += mom * hPrevBiasesDelta[i];
    hPrevBiasesDelta[i] = delta; // save delta
  }

  // 5. update hidden to output weights
  for (int i = 0; i < hoWeights.length(); ++i)  // 0..3 (4)
  {
    for (int j = 0; j < hoWeights[0].length()/numHidden; ++j) // 0..1 (2)
    {
      double delta = learn * oGrads[j] * hOutputs[i];  // hOutputs are inputs to next layer
      hoWeights[i][j] += delta;
      hoWeights[i][j] += mom * hoPrevWeightsDelta[i][j];
      hoPrevWeightsDelta[i][j] = delta;
    }
  }

  // 6. update hidden to output biases
  for (int i = 0; i < oBiases.length(); ++i)
  {
    double delta = learn * oGrads[i] * 1.0;
    oBiases[i] += delta;
    oBiases[i] += mom * oPrevBiasesDelta[i];
    oPrevBiasesDelta[i] = delta;
  }
} // UpdateWeights
