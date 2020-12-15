#include <mainwindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    readerMenu_ = new QMenu("Readers");
    bookMenu_ = new QMenu("Books");
    helpMenu_ = new QMenu("Help");

    mainMenu_ = new QMenuBar(this);
    mainMenu_->addMenu(readerMenu_);
    mainMenu_->addMenu(bookMenu_);
    mainMenu_->addMenu(helpMenu_);

    setMenuBar(mainMenu_);
}

MainWindow::~MainWindow()
{
    delete readerMenu_;
    delete bookMenu_;
    delete helpMenu_;
    delete mainMenu_;
}
