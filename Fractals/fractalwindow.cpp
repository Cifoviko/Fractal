#include "fractalwindow.h"
#include "complex.h"

#include <QLabel>

FractalWindow::FractalWindow(QWidget *parent)
    : QWidget(parent)
{


    mainLayout = new QHBoxLayout();


    fractal = new QLabel();
    mainLayout->addWidget(fractal);


    inputs = new QVBoxLayout();


    minRGBInput = new QHBoxLayout();

    rMinInput = new QSpinBox();
    rMinInput->setRange(0, 255);
    rMinInput->setValue(rMin);
    rMinInput->setWrapping(true);
    rMinInput->setButtonSymbols(QSpinBox::PlusMinus);
    rMinInput->setPrefix("minRed: ");
    minRGBInput->addWidget(rMinInput);

    bMinInput = new QSpinBox();
    bMinInput->setRange(0, 255);
    bMinInput->setValue(bMin);
    bMinInput->setWrapping(true);
    bMinInput->setButtonSymbols(QSpinBox::PlusMinus);
    bMinInput->setPrefix("minBlue: ");
    minRGBInput->addWidget(bMinInput);

    gMinInput = new QSpinBox();
    gMinInput->setRange(0, 255);
    gMinInput->setValue(gMin);
    gMinInput->setWrapping(true);
    gMinInput->setButtonSymbols(QSpinBox::PlusMinus);
    gMinInput->setPrefix("minGreen: ");
    minRGBInput->addWidget(gMinInput);

    inputs->addLayout(minRGBInput);


    maxRGBInput = new QHBoxLayout();

    rMaxInput = new QSpinBox();
    rMaxInput->setRange(0, 255);
    rMaxInput->setValue(rMax);
    rMaxInput->setWrapping(true);
    rMaxInput->setButtonSymbols(QSpinBox::PlusMinus);
    rMaxInput->setPrefix("maxRed: ");
    maxRGBInput->addWidget(rMaxInput);

    bMaxInput = new QSpinBox();
    bMaxInput->setRange(0, 255);
    bMaxInput->setValue(bMax);
    bMaxInput->setWrapping(true);
    bMaxInput->setButtonSymbols(QSpinBox::PlusMinus);
    bMaxInput->setPrefix("maxBlue: ");
    maxRGBInput->addWidget(bMaxInput);

    gMaxInput = new QSpinBox();
    gMaxInput->setRange(0, 255);
    gMaxInput->setValue(gMax);
    gMaxInput->setWrapping(true);
    gMaxInput->setButtonSymbols(QSpinBox::PlusMinus);
    gMaxInput->setPrefix("maxGreen: ");
    maxRGBInput->addWidget(gMaxInput);

    inputs->addLayout(maxRGBInput);


    czInput = new QHBoxLayout;

    zPowInput = new QSpinBox();
    zPowInput->setRange(-1e9, 1e9);
    zPowInput->setValue(zPow);
    zPowInput->setButtonSymbols(QSpinBox::PlusMinus);
    zPowInput->setPrefix("deg: ");
    czInput->addWidget(zPowInput);

    cxInput = new QDoubleSpinBox();
    cxInput->setDecimals(10);
    cxInput->setRange(-1e9, 1e9);
    cxInput->setValue(Const.x);
    cxInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    cxInput->setPrefix("cx: ");
    czInput->addWidget(cxInput);

    cyInput = new QDoubleSpinBox();
    cyInput->setDecimals(10);
    cyInput->setRange(-1e9, 1e9);
    cyInput->setValue(Const.y);
    cyInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    cyInput->setPrefix("cy: ");
    czInput->addWidget(cyInput);

    inputs->addLayout(czInput);


    lxyInput = new QHBoxLayout;

    leftXInput = new QDoubleSpinBox();
    leftXInput->setDecimals(10);
    leftXInput->setRange(-1e9, 1e9);
    leftXInput->setValue(pointX);
    leftXInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    leftXInput->setPrefix("leftX: ");
    lxyInput->addWidget(leftXInput);

    leftYInput = new QDoubleSpinBox();
    leftYInput->setDecimals(10);
    leftYInput->setRange(-1e9, 1e9);
    leftYInput->setValue(pointY);
    leftYInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    leftYInput->setPrefix("leftY: ");
    lxyInput->addWidget(leftYInput);

    inputs->addLayout(lxyInput);


    rxyInput = new QHBoxLayout;

    rightXInput = new QDoubleSpinBox();
    rightXInput->setDecimals(10);
    rightXInput->setRange(-1e9, 1e9);
    rightXInput->setValue(pointX + realHeight);
    rightXInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    rightXInput->setPrefix("rightX: ");
    rxyInput->addWidget(rightXInput);

    rightYInput = new QDoubleSpinBox();
    rightYInput->setDecimals(10);
    rightYInput->setRange(-1e9, 1e9);
    rightYInput->setValue(pointY + realWidht);
    rightYInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    rightYInput->setPrefix("rightY: ");
    rxyInput->addWidget(rightYInput);

    inputs->addLayout(rxyInput);


    infoperInput = new QHBoxLayout;

    infInput = new QDoubleSpinBox();
    infInput->setDecimals(10);
    infInput->setRange(-1e9, 1e9);
    infInput->setValue(infBarrier);
    infInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    infInput->setPrefix("inf: ");
    infoperInput->addWidget(infInput);

    operationsMaxInput = new QSpinBox();
    operationsMaxInput->setRange(1, 1e9);
    operationsMaxInput->setValue(operationsMax);
    operationsMaxInput->setButtonSymbols(QDoubleSpinBox::PlusMinus);
    operationsMaxInput->setPrefix("operations: ");
    infoperInput->addWidget(operationsMaxInput);

    inputs->addLayout(infoperInput);

    redrawButton = new QPushButton("Calculate");
    connect(redrawButton, SIGNAL(clicked()), SLOT(slotRedraw()));
    inputs->addWidget(redrawButton);

    mainLayout->addLayout(inputs);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    redraw();
}

void FractalWindow::paintPixel(int x, int y, int operations, QImage& img)
{
    int pointR = (((rMax - rMin) * operations) / operationsMax);
    int pointG = (((gMax - gMin) * operations) / operationsMax);
    int pointB = (((bMax - bMin) * operations) / operationsMax);
    img.setPixel(x, y, qRgb(pointR, pointG, pointB));
}

void FractalWindow::redraw()
{
    getAllParam();
    QImage img(pixelHeight, pixelWidht, QImage::Format_RGB888);
    for(int pX = 0; pX < pixelHeight; pX++)
    {
        for(int pY = 0; pY < pixelWidht; pY++)
        {
            paintPixel(pX, pY, runFunction(pX, pY), img);
        }
    }
    fractalImg = img;
    fractal->setPixmap(QPixmap::fromImage(img));
}

void FractalWindow::redrawWithSelection(int x, int y)
{
    if(x == -1 && y == -1)
    {
        fractal->setPixmap(QPixmap::fromImage(fractalImg));
        return;
    }
    getAllParam();
    QImage img = fractalImg;
    for(int pX = qMin(x, selectionStartX); pX <= qMax(x, selectionStartX); pX++)
    {
        img.setPixel(pX, selectionStartY, qRgb(255, 255, 255));
        img.setPixel(pX, y, qRgb(255, 255, 255));
    }
    for(int pY = qMin(y, selectionStartY); pY <= qMax(y, selectionStartY); pY++)
    {
        img.setPixel(selectionStartX, pY, qRgb(255, 255, 255));
        img.setPixel(x, pY, qRgb(255, 255, 255));
    }
    fractal->setPixmap(QPixmap::fromImage(img));
}

Complex FractalWindow::function(Complex& z)
{
    return (z.pow(zPow) + Const);
}

bool FractalWindow::checkInf(Complex &z)
{
    return ((z.x * z.x) + (z.y * z.y) < infBarrier);
}

int FractalWindow::runFunction(int x, int y)
{
    long double rX = pointX + (realHeight * x) / (long double)(pixelHeight);
    long double rY = pointY + (realWidht * y) / (long double)(pixelWidht);

    Complex z = Complex(rX, rY);

    int iterationCnt = 0;
    while(checkInf(z) && iterationCnt < operationsMax)
    {
        z = function(z);
        iterationCnt++;
    }

    return iterationCnt;
}

void FractalWindow::getAllParam()
{
    rMin = rMinInput->value();
    bMin = bMinInput->value();
    gMin = gMinInput->value();

    rMax = rMaxInput->value();
    bMax = bMaxInput->value();
    gMax = gMaxInput->value();

    zPow = zPowInput->value();
    Const = Complex(cxInput->value(), cyInput->value());

    infBarrier = infInput->value();
    operationsMax = operationsMaxInput->value();

    pointX = leftXInput->value();
    pointY = leftYInput->value();

    realHeight = rightXInput->value() - pointX;
    realWidht = rightYInput->value() - pointY;
}

void FractalWindow::slotRedraw()
{
    redraw();
}

void FractalWindow::mousePressEvent(QMouseEvent* pe)
{
    int x = pe->position().x();
    int y = pe->position().y();
    if((x <= pixelHeight) && (y <= pixelWidht))
    {
        selectionInProces = true;
        selectionStartX = x;
        selectionStartY = y;
    }
}

void FractalWindow::mouseReleaseEvent(QMouseEvent* pe)
{
    int x = pe->position().x();
    int y = pe->position().y();
    if(selectionInProces)
    {
        if((x <= pixelHeight) && (y <= pixelWidht))
        {
            selectionInProces = false;
            selectionEndX = x;
            selectionEndY = y;

            if(selectionStartX > selectionEndX)
            {
                int c = selectionStartX;
                selectionStartX = selectionEndX;
                selectionEndX = c;
            }
            if(selectionStartY > selectionEndY)
            {
                int c = selectionStartY;
                selectionStartY = selectionEndY;
                selectionEndY = c;
            }

            long double tx = pointX + (realHeight * selectionEndX) / (long double)(pixelHeight);
            long double ty = pointY + (realWidht * selectionEndX) / (long double)(pixelWidht);

            pointX = pointX + (realHeight * selectionStartX) / (long double)(pixelHeight);
            pointY = pointY + (realWidht * selectionStartY) / (long double)(pixelWidht);

            realHeight = tx - pointX;
            realWidht = ty - pointY;

            leftXInput->setValue(pointX);
            leftYInput->setValue(pointY);

            rightXInput->setValue(tx);
            rightYInput->setValue(ty);

            redraw();
        }
        else
        {
            selectionInProces = false;
            redrawWithSelection(-1, -1);
        }
    }
}

void FractalWindow::mouseMoveEvent(QMouseEvent* pe)
{
    int x = pe->position().x();
    int y = pe->position().y();
    if(selectionInProces)
    {
        if((x <= pixelHeight) && (y <= pixelWidht))
        {
            redrawWithSelection(x, y);
        }
        else
        {
            selectionInProces = false;
            redrawWithSelection(-1, -1);
        }
    }
}
