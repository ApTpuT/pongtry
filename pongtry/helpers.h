#ifndef HELPERS_H
#define HELPERS_H
#include <QApplication>


class Helpers
{
public:
        Helpers();

    static QList <QList<double>> MakeMatrix(int rows, int cols);
    static void ShowVector(QList <double> vector, int decimals, int valsPerLine, bool blankLine);
    static void ShowMatrix(QList <QList<double>> matrix, int numRows, int decimals);
    static double Error(QList <double> tValues, QList <double> yValues);
};

#endif // HELPERS_H
