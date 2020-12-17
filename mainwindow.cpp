#include <mainwindow.h>
#include <changemenu.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    readerMenu_ = new QMenu("Readers");
    bookMenu_   = new QMenu("Books");
    helpMenu_   = new QMenu("Help");

    //--------------------------------------------------------------------------------------------------
    //                                      Reader Menu Constumization
    //--------------------------------------------------------------------------------------------------

    auto* changeTitle = new ChangeMenu("Change title", "Print new title");
    auto* changeAuthor = new ChangeMenu("Change author", "Print new author");
    QAction act;

    readerMenu_->addAction("Add book");
    readerMenu_->addAction("Remove book");
    readerMenu_->addAction("Change book");
    readerMenu_->addAction("Get information about book");

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
}
