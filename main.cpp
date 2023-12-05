#include "mainwindow.h"
#include <QApplication>             // Add this line for qDebug()
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();
    return a.exec();
}
