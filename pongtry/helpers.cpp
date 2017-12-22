#include "helpers.h"
#include <qDebug>

Helpers::Helpers()
{

}

QList <QList<double>> Helpers::MakeMatrix(int rows, int cols)
   {
     QList <QList<double>> result;
     QList<double> temp;
     for (int i = 0; i < rows; ++i){
      for (int j = 0; j < cols; ++j) temp+=0;
       result.push_front(temp);
     }

     return result;
   }

void Helpers::ShowVector(QList <double> vector, int decimals, int valsPerLine, bool blankLine)
   {
     /*for (int i = 0; i < vector.length(); ++i)
     {
       if (i > 0 && i % valsPerLine == 0) // max of 12 values per row
         //qDebug() << "";
       if (vector[i] >= 0.0) //qDebug() <<" ";
       //qDebug() <<QString::number(vector[i]); // n decimals
     }
     if (blankLine) //qDebug() <<"\n";*/
   }

void Helpers::ShowMatrix(QList <QList<double>> matrix, int numRows, int decimals)
   {
     int ct = 0;
     if (numRows == -1) numRows = std::numeric_limits<quintptr>::max(); // if numRows == -1, show all rows
     for (int i = 0; i < matrix.length() && ct < numRows; ++i)
     {
       for (int j = 0; j < matrix[0].length(); ++j)
       {
         //if (matrix[i][j] >= 0.0) //qDebug() <<" "; // blank space instead of '+' sign
         //qDebug() <<QString::number(matrix[i][j]);
       }
       //qDebug() <<"";
       ++ct;
     }
     //qDebug() <<"";
   }

double Helpers::Error(QList <double> tValues, QList <double> yValues)
   {
     double sum = 0.0;
     for (int i = 0; i < tValues.length(); ++i)
       sum += (tValues[i] - yValues[i]) * (tValues[i] - yValues[i]);
     return sqrt(sum);
   }
