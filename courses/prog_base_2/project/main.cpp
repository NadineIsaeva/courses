#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    QLabel ltest("<h2><font color = green>Let's start working on project!<\font><h2>");
    ltest.show();

    return a.exec();
}
