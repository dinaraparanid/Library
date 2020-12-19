#include <mainwindow.h>
#include <changemenu.h>
#include <messagedialog.h>
#include <reader.h>
#include <book.h>

auto bookSys = booksys::BookSystem::getInstance();
auto readSys = read::ReaderBase::getInstance();

MainWindow::MainWindow(QWidget* parent) noexcept :
    QMainWindow (parent),
    readerMenu_ (new QMenu("Readers")),
    bookMenu_   (new QMenu("Books")),
    helpMenu_   (new QMenu("Help")),
    giveaway_   (new QMenu("Give / Get book"))
{
    //--------------------------------------------------------------------------
    //                              Readers menu
    //--------------------------------------------------------------------------

    auto* addReader     = new QAction("Add reader");
    auto* removeReader  = new QAction("Remove reader");
    auto* infoReader    = new QAction("Get information about reader");

    auto* addReadName   = new QString;
    auto* addReadFamily = new QString;
    auto* addReaderMenu = new chng::Input2("Add reader", "Input first name", "Input second family",
                                           addReadName, addReadFamily);

    auto* remReadName   = new QString;
    auto* remReadFamily = new QString;
    auto* remReaderMenu = new chng::Input2("Remove reader", "Input first name", "Input second family",
                                           remReadName, remReadFamily);

    auto* infoReadName   = new QString;
    auto* infoReadFamily = new QString;
    auto* infoReaderMenu = new chng::Input2("Get information about reader", "Input first name", "Input second family",
                                           infoReadName, infoReadFamily);

    readerMenu_->addAction(addReader);
    readerMenu_->addAction(removeReader);
    readerMenu_->addAction(infoReader);

    QObject::connect(addReader,         SIGNAL(triggered()), addReaderMenu,     SLOT(exec()));
    //QObject::connect(addReaderMenu,     SIGNAL(okPressed()), this,              SLOT(addReader(addReadName, addReadFamily)));
    QObject::connect(removeReader,      SIGNAL(triggered()), remReaderMenu,     SLOT(exec()));
    //QObject::connect(remReaderMenu,     SIGNAL(okPressed()), this,              SLOT(removeReader(remReadName, remReadFamily)));
    QObject::connect(infoReader,        SIGNAL(triggered()), infoReaderMenu,    SLOT(exec()));
    //QObject::connect(infoReaderMenu,    SIGNAL(okPressed()), this,              SLOT(findReader(infoReadName, infoReadFamily)));

    //--------------------------------------------------------------------------
    //                              Books menu
    //--------------------------------------------------------------------------

    auto* addBook       = new QAction("Add book");
    auto* removeBook    = new QAction("Remove book");
    auto* infoBook      = new QAction("Get information about book");

    auto* addBookTitle  = new QString;
    auto* addBookAuthor = new QString;
    auto* addBookMenu   = new chng::Input2("Add book", "Input title", "Input author",
                                           addBookTitle, addBookAuthor);

    auto* remBookTitle  = new QString;
    auto* remBookAuthor = new QString;
    auto* remBookMenu   = new chng::Input2("Remove book", "Input title", "Input author",
                                           remBookTitle, remBookAuthor);

    auto* infoBookTitle     = new QString;
    auto* infoBookAuthor    = new QString;
    auto* infoBookMenu      = new chng::Input2("Get information about book", "Input title", "Input author",
                                                infoBookTitle, infoBookAuthor);

    bookMenu_->addAction(addBook);
    bookMenu_->addAction(removeBook);
    bookMenu_->addAction(infoBook);

    QObject::connect(addBook,         SIGNAL(triggered()), addBookMenu,     SLOT(show()));
    //QObject::connect(addBookMenu,     SIGNAL(okPressed()), this,            SLOT(addBook(addBookTitle, addBookAuthor)));
    QObject::connect(removeBook,      SIGNAL(triggered()), remBookMenu,     SLOT(show()));
    //QObject::connect(remBookMenu,     SIGNAL(okPressed()), this,            SLOT(removeReader(remBookTitle, remBookAuthor)));
    QObject::connect(infoBook,        SIGNAL(triggered()), infoBookMenu,    SLOT(show()));
    //QObject::connect(infoBookMenu,    SIGNAL(okPressed()), this,            SLOT(findReader(infoBookTitle, infoBookAuthor)));

    //--------------------------------------------------------------------------
    //                              Giveaway menu
    //--------------------------------------------------------------------------

    auto* giveBook  = new QAction("Give book");
    auto* getBook   = new QAction("Get book");

    auto* giveBookName      = new QString;
    auto* giveBookFamily    = new QString;
    auto* giveBookMenu1     = new chng::Input2("To Who", "Input first name", "Input second name",
                                                giveBookName, giveBookFamily);

    auto* giveBookTitle     = new QString;
    auto* giveBookAuthor    = new QString;
    auto* giveBookMenu2     = new chng::Input2("What book", "Input title", "Input author",
                                                giveBookTitle, giveBookAuthor);

    auto* getBookName   = new QString;
    auto* getBookFamily = new QString;
    auto* getBookMenu1  = new chng::Input2("From Who", "Input first name", "Input second name",
                                           getBookName, getBookFamily);

    auto* getBookTitle  = new QString;
    auto* getBookAuthor = new QString;
    auto* getBookMenu2  = new chng::Input2("What book", "Input title", "Input author",
                                          getBookTitle, getBookAuthor);

    giveaway_->addAction(giveBook);
    giveaway_->addAction(getBook);

    QObject::connect(giveBook,      SIGNAL(triggered()), giveBookMenu1,     SLOT(show()));
    QObject::connect(giveBookMenu1, SIGNAL(okPressed()), giveBookMenu2,     SLOT(show()));
    QObject::connect(getBook,       SIGNAL(triggered()), getBookMenu1,      SLOT(show()));
    QObject::connect(getBookMenu1,  SIGNAL(okPressed()), getBookMenu2,      SLOT(show()));

    //--------------------------------------------------------------------------
    //                              Main Menu
    //--------------------------------------------------------------------------

    mainMenu_ = new QMenuBar(this);

    mainMenu_->addMenu(readerMenu_);
    mainMenu_->addMenu(bookMenu_);
    mainMenu_->addMenu(helpMenu_);
    mainMenu_->addMenu(giveaway_);

    setMenuBar(mainMenu_);
}

MainWindow::~MainWindow()
{
    delete readerMenu_;
    delete bookMenu_;
    delete helpMenu_;
    delete giveaway_;
}
