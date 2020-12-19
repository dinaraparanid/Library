#include "mainwindow.h"
#include "messagedialog.h"
#include "changemenu.h"
#include "messagedialog.h"

#include <QApplication>
#include <iostream>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    MainWindow mainMenu;
    mainMenu.setWindowState(Qt::WindowMaximized);
    mainMenu.show();

    return a.exec();
}
