#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QPalette>
#include <QScreen>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    const auto size = a.screens().first()->geometry();

    auto* mainMenu = new MainWindow;
    mainMenu->setWindowState(Qt::WindowMaximized);
    mainMenu->setFixedSize(size.width(), size.height());

    auto* readerMenu = new QWidget;
    readerMenu->setWindowState(Qt::WindowMaximized);
    readerMenu->setFixedSize(size.width(), size.height());

    auto* bookMenu = new QWidget;
    bookMenu->setWindowState(Qt::WindowMaximized);
    bookMenu->setFixedSize(size.width(), size.height());

    auto* buttonsFont = new QFont("SansSerif", 16, QFont::Cursive);
    buttonsFont->setItalic(true);
    buttonsFont->setBold(true);

    auto* helloFont = new QFont("Calibri", 20);
    helloFont->setItalic(true);
    helloFont->setBold(true);
    helloFont->setUnderline(true);

    auto* palette = new QPalette;
    palette->setColor(QPalette::Background, Qt::yellow);

    readerMenu->setAutoFillBackground(true);
    readerMenu->setPalette(*palette);

    bookMenu->setAutoFillBackground(true);
    bookMenu->setPalette(*palette);

    mainMenu->setAutoFillBackground(true);
    mainMenu->setPalette(*palette);

    //-------------------------------------------------------------------------------------------------
    //                                  Incorrect Input costumization
    //-------------------------------------------------------------------------------------------------

    auto* incorrectInputWindow = new QWidget;
    incorrectInputWindow->setGeometry(size.width() / 2 - size.height() / 4,
                                      size.height() / 2 - size.height() / 10,
                                      size.height() / 2, size.height() / 5);

    incorrectInputWindow->setFixedSize(size.height() / 2,size.height() / 5);

    auto* incorrectHello = new QLabel("Incorrect input. Try again", incorrectInputWindow);
    incorrectHello->setGeometry(size.height() / 8, - size.height() / 2.2,
                               size.height(), size.height());

    incorrectHello->setFont(*helloFont);

    auto* incorrectInputOkButton = new QPushButton("OK", incorrectInputWindow);
    incorrectInputOkButton->setGeometry(size.height() / 5, size.height() / 10,
                                        size.height() / 10, size.height() / 20);

    incorrectInputOkButton->setFont(*buttonsFont);

    QObject::connect(incorrectInputOkButton, SIGNAL(pressed()), incorrectInputWindow, SLOT(close()));

    //-------------------------------------------------------------------------------------------------
    //                                  Sure Dialog costumization
    //-------------------------------------------------------------------------------------------------

    auto* sure = new QWidget;
    sure->setGeometry(size.width() / 2 - size.height() / 4,
                      size.height() / 2 - size.height() / 10,
                      size.height() / 2, size.height() / 5);

    sure->setFixedSize(size.height() / 2,size.height() / 5);

    auto* sureHello = new QLabel("Are you sure you want to do this?", sure);
    sureHello->setGeometry(size.height() / 12, - size.height() / 2.2,
                           size.height(), size.height());

    sureHello->setFont(*helloFont);

    auto* sureYesButton = new QPushButton("YES", sure);
    sureYesButton->setGeometry(size.height() / 15, size.height() / 10,
                               size.height() / 10, size.height() / 20);

    sureYesButton->setFont(*buttonsFont);

    auto* sureNoButton = new QPushButton("NO", sure);
    sureNoButton->setGeometry(size.height() / 3, size.height() / 10,
                               size.height() / 10, size.height() / 20);

    sureNoButton->setFont(*buttonsFont);

    QObject::connect(sureYesButton, SIGNAL(pressed()), sure, SLOT(close()));
    QObject::connect(sureNoButton, SIGNAL(pressed()), sure, SLOT(close()));

    //-------------------------------------------------------------------------------------------------
    //                                  Main Menu costumization
    //-------------------------------------------------------------------------------------------------

    auto* mainMenuHello = new QLabel("LIBRARY INTERFACE", mainMenu);
    mainMenuHello->setGeometry(size.width() / 2 - size.width() / 25,
                               size.height() / 2 - size.height() / 5,
                               size.height() / 2, size.height() / 20);

    mainMenuHello->setFont(*helloFont);

    auto* mainMenuReadButton = new QPushButton("Readers", mainMenu);
    mainMenuReadButton->setGeometry(size.width() / 2 - size.width() / 8,
                                    size.height() / 2 - size.height() / 5 + size.width() / 18,
                                    size.height() / 2, size.height() / 20);

    mainMenuReadButton->setFont(*buttonsFont);

    auto* mainMenuBookButton = new QPushButton("Books", mainMenu);
    mainMenuBookButton->setGeometry(size.width() / 2 - size.width() / 8,
                                    size.height() / 2 - size.height() / 5 + 2 * size.width() / 18,
                                    size.height() / 2, size.height() / 20);

    mainMenuBookButton->setFont(*buttonsFont);

    auto* mainMenuExitButton = new QPushButton("Exit", mainMenu);
    mainMenuExitButton->setGeometry(size.width() / 2 - size.width() / 8,
                                    size.height() / 2 - size.height() / 5 + 3 * size.width() / 18,
                                    size.height() / 2, size.height() / 20);

    mainMenuExitButton->setFont(*buttonsFont);

    QObject::connect(mainMenuExitButton, SIGNAL(pressed()), mainMenu, SLOT(close()));
    QObject::connect(mainMenuReadButton, SIGNAL(pressed()), readerMenu, SLOT(show()));
    QObject::connect(mainMenuReadButton, SIGNAL(pressed()), mainMenu, SLOT(hide()));
    QObject::connect(mainMenuBookButton, SIGNAL(pressed()), bookMenu, SLOT(show()));
    QObject::connect(mainMenuBookButton, SIGNAL(pressed()), mainMenu, SLOT(hide()));

    //-------------------------------------------------------------------------------------------------
    //                              Reading Menu costumization
    //-------------------------------------------------------------------------------------------------

    auto* readerMenuHello = new QLabel("READING MENU", readerMenu);
    readerMenuHello->setGeometry(size.width() / 2 - size.width() / 35,
                                 size.height() / 2 - size.height() / 5,
                                 size.height() / 2, size.height() / 20);

    readerMenuHello->setFont(*helloFont);

    auto* readerMenuExitButton = new QPushButton("Exit", readerMenu);
    readerMenuExitButton->setGeometry(size.width() / 2 - size.width() / 8,
                                      size.height() / 2 - size.height() / 5 + size.width() / 18,
                                      size.height() / 2, size.height() / 20);

    readerMenuExitButton->setFont(*buttonsFont);

    QObject::connect(readerMenuExitButton, SIGNAL(pressed()), mainMenu, SLOT(show()));
    QObject::connect(readerMenuExitButton, SIGNAL(pressed()), readerMenu, SLOT(close()));

    //-------------------------------------------------------------------------------------------------
    //                              Books Menu costumization
    //-------------------------------------------------------------------------------------------------

    auto* bookMenuHello = new QLabel("BOOKS MENU", bookMenu);
    bookMenuHello->setGeometry(size.width() / 2 - size.width() / 55,
                               size.height() / 2 - size.height() / 5,
                               size.height() / 2, size.height() / 20);

    bookMenuHello->setFont(*helloFont);

    auto* bookMenuExitButton = new QPushButton("Exit", bookMenu);
    bookMenuExitButton->setGeometry(size.width() / 2 - size.width() / 8,
                                    size.height() / 2 - size.height() / 5 + size.width() / 18,
                                    size.height() / 2, size.height() / 20);

    bookMenuExitButton->setFont(*buttonsFont);

    QObject::connect(bookMenuExitButton, SIGNAL(pressed()), mainMenu, SLOT(show()));
    QObject::connect(bookMenuExitButton, SIGNAL(pressed()), bookMenu, SLOT(close()));

    mainMenu->show();
    return a.exec();
}
