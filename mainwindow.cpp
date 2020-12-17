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

    QAction addBook("Add book");
    QAction removeBook("Remove book");
    QAction getInfoBook("Get information about book");

    QMenu editBook("Edit book");
    editBook.addAction("Edit title");
   // ChangeMenu* editTitleBook = new ChangeMenu("Edit title", "Input new title");

    readerMenu_->addAction(&addBook);
    readerMenu_->addAction(&removeBook);
    readerMenu_->addAction(&getInfoBook);
    readerMenu_->addMenu(&editBook);
    readerMenu_->addAction("Kek");



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
