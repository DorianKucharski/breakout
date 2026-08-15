#include <QApplication>
#include "mainwindow.h"
#include <QVector>
#include <QBrush>
#include <QList>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800,600);
    w.show();
    return a.exec();
}
