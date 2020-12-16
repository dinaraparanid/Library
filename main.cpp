#include "mainwindow.h"
#include <changemenu.h>
#include <QApplication>
#include <iostream>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    MainWindow mainMenu;
    mainMenu.show();

    return a.exec();
}
