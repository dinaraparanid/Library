#include "mainwindow.h"
#include "messagedialog.h"
#include "changemenu.h"
#include "messagedialog.h"

#include <QApplication>
#include <iostream>

/**
  Доделать:
    1) Добавить корректность даты
    2) Пофиксить изменение и их последствия
    3) Добавить информационные окна
    4) добавить таблицу со всем

  Доп:
    5) Добавить help
    6) Добавить жанры и кол-во страниц
    7) Добавить возможность повторения челов с 1 именем
    8) Добавить окна отображения должников
*/

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow mainMenu;
    mainMenu.setWindowState(Qt::WindowMaximized);
    mainMenu.show();

    return app.exec();
}
