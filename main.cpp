#include "mainwindow.h"
#include <changemenu.h>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    MainWindow mainMenu;
    mainMenu.show();

   /* ChangeMenu<_, _> ask("Title", "Input name", "Input family");
    ask.show();*/

    return a.exec();
}
