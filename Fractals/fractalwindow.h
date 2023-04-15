#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include "complex.h"
#include <algorithm>
#include <math.h>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QPair>
#include <QMouseEvent>

class FractalWindow : public QWidget
{
    Q_OBJECT

public:
    FractalWindow(QWidget *parent = 0);
    int pixelHeight = 750, pixelWidht = 750;
    long double pointX = -4.5, pointY = -4.5;
    long double realHeight = 9, realWidht = 9;
    int rMin = 0, rMax = 250, gMin = 0, gMax = 250, bMin = 0, bMax = 0;
    long double infBarrier = 1000000000;
    Complex Const = Complex(0.14, -0.11);
    int zPow = -6;
    void redraw();
    QPushButton* redrawButton;

protected:
    void redrawWithSelection(int x, int y);
    QImage fractalImg;
    bool selectionInProces = false;
    int selectionStartX, selectionStartY;
    int selectionEndX, selectionEndY;

    QLabel* fractal;
    QHBoxLayout* mainLayout;
    QVBoxLayout* inputs;

    QHBoxLayout* minRGBInput;
    QSpinBox* rMinInput;
    QSpinBox* gMinInput;
    QSpinBox* bMinInput;

    QHBoxLayout* maxRGBInput;
    QSpinBox* rMaxInput;
    QSpinBox* gMaxInput;
    QSpinBox* bMaxInput;

    QHBoxLayout* czInput;
    QSpinBox* zPowInput;
    QDoubleSpinBox* cxInput;
    QDoubleSpinBox* cyInput;

    QHBoxLayout* lxyInput;
    QDoubleSpinBox* leftXInput;
    QDoubleSpinBox* leftYInput;
    QHBoxLayout* rxyInput;
    QDoubleSpinBox* rightXInput;
    QDoubleSpinBox* rightYInput;

    QHBoxLayout* infoperInput;
    QDoubleSpinBox* infInput;
    QSpinBox* operationsMaxInput;

    int operationsMax = 25;
    int runFunction(int x, int y);
    bool checkInf(Complex& z);
    Complex function(Complex& z);
    void paintPixel(int x, int y, int operations, QImage& img);
    void getAllParam();

public slots:
    void slotRedraw();
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent(QMouseEvent* pe);

};

#endif // FRACTALWINDOW_H
