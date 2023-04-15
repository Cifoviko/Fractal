#include "mainwindow.h"
#include "fractalwindow.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QPair>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FractalWindow* window = new FractalWindow(/*new QWidget*/);
    window->show();

    return a.exec();
}
