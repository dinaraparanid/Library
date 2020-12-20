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

    auto* addReader             = new QAction("Add reader");
    auto* removeReader          = new QAction("Remove reader");
    auto* infoReader            = new QAction("Get information about reader");

    auto* editReader            = new QMenu("Edit Reader");
    auto* editName              = new QAction("Edit first name");
    auto* editFamily            = new QAction("Edit second name");

    editReader->addAction(editName);
    editReader->addAction(editFamily);

    auto* name                  = new QString;
    auto* family                = new QString;
    auto* editsr                = new QString;

    auto* addReaderMenu         = new chng::Input2("Add reader", "Input first name", "Input second name", name, family);
    auto* remReaderMenu         = new chng::Input2("Remove reader", "Input first name", "Input second name", name, family);
    auto* infoReaderMenu        = new chng::Input2("Reader's information", "Input first name", "Input second name", name, family);
    auto* editReaderMenu1       = new chng::Input2("Edit reader", "Input first name", "Input second name", name, family);
    auto* editReaderMenu2       = new chng::Input2("Edit reader", "Input first name", "Input second name", name, family);
    auto* editNameMenu          = new chng::Input1("Edit name", "Input new first name", editsr);
    auto* editFamilyMenu        = new chng::Input1("Edit family", "Input new second name", editsr);

    readerMenu_->addAction(addReader);
    readerMenu_->addAction(removeReader);
    readerMenu_->addAction(infoReader);
    readerMenu_->addMenu(editReader);

    QObject::connect(addReader,         SIGNAL(triggered()), addReaderMenu,     SLOT(exec()));
    QObject::connect(addReaderMenu,     &chng::Input2::okPressed, [this, name, family]          () { this->addReader(*name, *family); });

    QObject::connect(removeReader,      SIGNAL(triggered()), remReaderMenu,     SLOT(exec()));
    QObject::connect(remReaderMenu,     &chng::Input2::okPressed, [this, name, family]          () { this->removeReader(*name, *family); });

    QObject::connect(infoReader,        SIGNAL(triggered()), infoReaderMenu,    SLOT(exec()));
    QObject::connect(infoReaderMenu,    &chng::Input2::okPressed, [this, name, family]          () { this->findReader(*name, *family); });

    QObject::connect(editName,          SIGNAL(triggered()), editReaderMenu1,   SLOT(exec()));
    QObject::connect(editReaderMenu1,   SIGNAL(okPressed()), editNameMenu,      SLOT(exec()));
    QObject::connect(editNameMenu,      &chng::Input1::okPressed, [this, name, family, editsr]    () { this->changeName(*name, *family, *editsr); });

    QObject::connect(editFamily,        SIGNAL(triggered()), editReaderMenu2,   SLOT(exec()));
    QObject::connect(editReaderMenu2,   SIGNAL(okPressed()), editFamilyMenu,    SLOT(exec()));
    QObject::connect(editFamilyMenu,    &chng::Input1::okPressed, [this, name, family, editsr]    () { this->changeFamily(*name, *family, *editsr); });

    //--------------------------------------------------------------------------
    //                              Books menu
    //--------------------------------------------------------------------------

    auto* addBook           = new QAction("Add book");
    auto* removeBook        = new QAction("Remove books");
    auto* addSimple         = new QAction("Add existing book");
    auto* removeSimple      = new QAction("Remove one book");
    auto* infoBook          = new QAction("Get information about book");

    auto* editBook          = new QMenu("Edit book");
    auto* editTitle         = new QAction("Edit title");
    auto* editAuthor        = new QAction("Edit author");

    editBook->addAction(editTitle);
    editBook->addAction(editAuthor);

    auto* title             = new QString;
    auto* author            = new QString;
    auto* editsb            = new QString;

    auto* addBookMenu1      = new chng::Input2("Add new book", "Input title", "Input author", title, author);
    auto* addBookMenu2      = new chng::Input2("Add books", "Input title", "Input author", title, author);
    auto* addBookMenu3      = new chng::Input1("Number of book", "Input number of book", editsb);
    auto* remBookMenu1      = new chng::Input2("Remove books", "Input title", "Input author", title, author);
    auto* remBookMenu2      = new chng::Input2("Remove book", "Input title", "Input author", title, author);
    auto* remBookMenu3      = new chng::Input1("Number of book", "Input number of book", editsb);
    auto* infoBookMenu      = new chng::Input2("Get information about book", "Input title", "Input author", title, author);
    auto* editBookMenu1     = new chng::Input2("Edit book", "Input title", "Input author", title, author);
    auto* editBookMenu2     = new chng::Input2("Edit book", "Input title", "Input author", title, author);
    auto* editTitleMenu     = new chng::Input1("Edit title", "Input new title", editsb);
    auto* editAuthorMenu    = new chng::Input1("Edit author", "Input new author", editsb);

    bookMenu_->addAction(addBook);
    bookMenu_->addAction(removeBook);
    bookMenu_->addAction(infoBook);
    bookMenu_->addAction(addSimple);
    bookMenu_->addAction(removeSimple);
    bookMenu_->addMenu(editBook);

    QObject::connect(addBook,           SIGNAL(triggered()), addBookMenu1,      SLOT(exec()));
    QObject::connect(addBookMenu1,      &chng::Input2::okPressed, [this, title, author]         () { this->addBook(*title, *author); });

    QObject::connect(addSimple,         SIGNAL(triggered()), addBookMenu2,      SLOT(exec()));
    QObject::connect(addBookMenu2,      SIGNAL(okPressed()), addBookMenu3,      SLOT(exec()));
    QObject::connect(addBookMenu3,      &chng::Input1::okPressed, [this, title, author, editsb] () { this->addSimpleBook(*title, *author, editsb->toUInt()); });

    QObject::connect(removeBook,        SIGNAL(triggered()), remBookMenu1,      SLOT(exec()));
    QObject::connect(remBookMenu1,      &chng::Input2::okPressed, [this, title, author]         () { this->removeBook(*title, *author); });

    QObject::connect(removeSimple,      SIGNAL(triggered()), remBookMenu2,      SLOT(exec()));
    QObject::connect(remBookMenu2,      SIGNAL(okPressed()), remBookMenu3,      SLOT(exec()));
    QObject::connect(remBookMenu3,      &chng::Input1::okPressed, [this, title, author, editsb] () { this->removeSimpleBook(*title, *author, editsb->toUInt()); });

    QObject::connect(infoBook,          SIGNAL(triggered()), infoBookMenu,      SLOT(exec()));
    QObject::connect(infoBookMenu,      &chng::Input2::okPressed, [this, title, author]         () { this->findBook(*title, *author); });

    QObject::connect(editTitle,         SIGNAL(triggered()), editBookMenu1,     SLOT(exec()));
    QObject::connect(editBookMenu1,     SIGNAL(okPressed()), editTitleMenu,     SLOT(exec()));
    QObject::connect(editTitleMenu,     &chng::Input1::okPressed, [this, title, author, editsb] () { this->changeTitle(*title, *author, *editsb); });

    QObject::connect(editAuthor,        SIGNAL(triggered()), editBookMenu2,     SLOT(exec()));
    QObject::connect(editBookMenu2,     SIGNAL(okPressed()), editAuthorMenu,    SLOT(exec()));
    QObject::connect(editAuthorMenu,    &chng::Input1::okPressed, [this, title, author, editsb] () { this->changeAuthor(*title, *author, *editsb); });

    //--------------------------------------------------------------------------
    //                              Giveaway menu
    //--------------------------------------------------------------------------

    auto* giveBook          = new QAction("Give book");
    auto* getBook           = new QAction("Get book");

    auto* nameg             = new QString;
    auto* familyg           = new QString;
    auto* titleg            = new QString;
    auto* authorg           = new QString;

    std::uint8_t giveDay    = 0;
    std::uint8_t giveMonth  = 0;
    std::uint16_t giveYear  = 0;

    auto* giveBookMenu1     = new chng::Input2("To Who", "Input first name", "Input second name", nameg, familyg);
    auto* giveBookMenu2     = new chng::Input2("What book", "Input title", "Input author", titleg, authorg);
    auto* giveBookMenu3     = new chng::Input3("Finish date", "Input day", "Input month", "Input year", &giveDay, &giveMonth, &giveYear);
    auto* getBookMenu1      = new chng::Input2("From Who", "Input first name", "Input second name", nameg, familyg);
    auto* getBookMenu2      = new chng::Input2("What book", "Input title", "Input author", titleg, authorg);

    giveaway_->addAction(giveBook);
    giveaway_->addAction(getBook);

    const auto giveDate = std::make_tuple(giveDay, giveMonth, giveYear);

    QObject::connect(giveBook,      SIGNAL(triggered()), giveBookMenu1,     SLOT(exec()));
    QObject::connect(giveBookMenu1, SIGNAL(okPressed()), giveBookMenu2,     SLOT(exec()));
    QObject::connect(giveBookMenu2, SIGNAL(okPressed()), giveBookMenu3,     SLOT(exec()));
    QObject::connect(giveBookMenu3, &chng::Input3::okPressed, [this, nameg, familyg, titleg, authorg, giveDate]
    { this->giveBookToReader(*nameg, *familyg, *titleg, *authorg, giveDate); } );

    QObject::connect(getBook,       SIGNAL(triggered()), getBookMenu1,      SLOT(exec()));
    QObject::connect(getBookMenu1,  SIGNAL(okPressed()), getBookMenu2,      SLOT(exec()));
    QObject::connect(getBookMenu2, &chng::Input2::okPressed, [this, nameg, familyg, titleg, authorg]
    { this->getBookFromReader(*nameg, *familyg, *titleg, *authorg); } );

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

void MainWindow::addBook(QString&& title, QString&& author) noexcept
{
    if (bookSys->addBook(title, author))
    {
        qDebug("Add the book %s %s", title.toStdString().c_str(), author.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully added");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("The book %s %s is not added (found)", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("The book is already exists");
        fail->exec();
        delete fail;
    }

    emit pressedAddBook();
}

void MainWindow::addBook(const QString& title, const QString& author) noexcept
{
    if (bookSys->addBook(title, author))
    {
        qDebug("Add the book %s %s", title.toStdString().c_str(), author.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully added");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("The book %s %s is not added (found)", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("The book is already exists");
        fail->exec();
        delete fail;
    }

    emit pressedAddBook();
}

void MainWindow::removeBook(QString&& title, QString&& author) noexcept
{
    if (bookSys->removeBook(title, author))
    {
        qDebug("Remove the book %s %s", title.toStdString().c_str(), author.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully removed");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("The book %s %s is not removed (not found)", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("The book is not found");
        fail->exec();
        delete fail;
    }

    emit pressedRemoveBook();
}

void MainWindow::removeBook(const QString& title, const QString& author) noexcept
{
    if (bookSys->removeBook(title, author))
    {
        qDebug("Remove the book %s %s", title.toStdString().c_str(), author.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully removed");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("The book %s %s is not removed (not found)", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("The book is not found");
        fail->exec();
        delete fail;
    }

    emit pressedRemoveBook();
}

void MainWindow::findBook(QString&& title, QString&& author) noexcept
{
    if (bookSys->find(title, author) != bookSys->cend())
    {
        qDebug("The book %s %s is found", title.toStdString().c_str(), author.toStdString().c_str());
    }

    else
    {
        qDebug("The book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("The book is not found");
        fail->exec();
        delete fail;
    }

    emit pressedFindBook();
}

void MainWindow::findBook(const QString& title, const QString& author) noexcept
{
    if (bookSys->find(title, author) != bookSys->cend())
    {
        qDebug("The book %s %s is found", title.toStdString().c_str(), author.toStdString().c_str());
    }

    else
    {
        qDebug("The book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("The book is not found");
        fail->exec();
        delete fail;
    }

    pressedFindBook();
}

void MainWindow::addReader(QString&& name, QString&& family) noexcept
{
    if (readSys->addReader(name, family))
    {
        qDebug("Reader %s %s is added", name.toStdString().c_str(), family.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully added");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Reader %s %s is not added (found)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is already exists");
        fail->exec();
        delete fail;
    }

    emit pressedAddReader();
}

void MainWindow::addReader(const QString& name, const QString& family) noexcept
{
    if (readSys->addReader(name, family))
    {
        qDebug("Reader %s %s is added", name.toStdString().c_str(), family.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully added");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Reader %s %s is not added (found)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is already exists");
        fail->exec();
        delete fail;
    }

    emit pressedAddReader();
}

void MainWindow::removeReader(QString&& name, QString&& family) noexcept
{
    if (readSys->removeReader(name, family))
    {
        qDebug("Reader %s %s is removed", name.toStdString().c_str(), family.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully removed");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Reader %s %s is not removed (not fund)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    emit pressedRemoveReader();
}

void MainWindow::removeReader(const QString& name, const QString& family) noexcept
{
    if (readSys->removeReader(name, family))
    {
        qDebug("Reader %s %s is removed", name.toStdString().c_str(), family.toStdString().c_str());
        auto* succes = new MessageDialog("Succesfully removed");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Reader %s %s is not removed (not found)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    emit pressedRemoveReader();
}

void MainWindow::findReader(QString&& name, QString&& family) noexcept
{
    if (readSys->find(name, family) != readSys->cend())
    {
        qDebug("Reader %s %s is found", name.toStdString().c_str(), family.toStdString().c_str());
    }

    else
    {
        qDebug("Reader %s %s is not found", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    emit pressedFindReader();
}

void MainWindow::findReader(const QString& name, const QString& family) noexcept
{
    if (readSys->find(name, family) != readSys->cend())
    {
        qDebug("Reader %s %s is added", name.toStdString().c_str(), family.toStdString().c_str());
    }

    else
    {
        qDebug("Reader %s %s is not found", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    emit pressedFindReader();
}

void MainWindow::getHelp() noexcept
{
    qDebug("HELP");
    emit pressedHelp();
}

void MainWindow::MainWindow::giveBookToReader(QString&& name, QString&& family, QString&& title, QString&& author, booksys::date end) noexcept
{
    const auto guy = readSys->find(name, family);

    if (guy == readSys->cend())
    {
        qDebug("Reader %s %s is not found (giveBook)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    else
    {
        const auto theBook = bookSys->find(title, author);

        if (theBook != bookSys->cend())
        {
            const auto book = theBook->getUnused();

            if (book == theBook->cend())
            {
                qDebug("All Books %s %s are given", title.toStdString().c_str(), author.toStdString().c_str());
                auto* noFree = new MessageDialog("All Book are given");
                noFree->exec();
                delete noFree;
            }

            else
            {
                qDebug("Book %s %s is given to Reader %s %s", title.toStdString().c_str(), author.toStdString().c_str(), name.toStdString().c_str(), family.toStdString().c_str());
                guy->startReading(std::make_shared<booksys::Book>(*book), end);
                auto* start = new MessageDialog("Book is given");
                start->exec();
                delete start;
            }
        }

        else
        {
            qDebug("The Book %s %s is not found (giveBook)", title.toStdString().c_str(), author.toStdString().c_str());
            auto* fail = new MessageDialog("Book is not found");
            fail->exec();
            delete fail;
        }
    }

    emit pressedGiveBook();
}

void MainWindow::MainWindow::giveBookToReader(const QString& name, const QString& family, const QString& title, const QString& author, booksys::date end) noexcept
{
    const auto guy = readSys->find(name, family);

    if (guy == readSys->cend())
    {
        qDebug("Reader %s %s is not found (giveBook)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    else
    {
        const auto theBook = bookSys->find(title, author);

        if (theBook != bookSys->cend())
        {
            const auto book = theBook->getUnused();

            if (book == theBook->cend())
            {
                qDebug("All Books %s %s are given", title.toStdString().c_str(), author.toStdString().c_str());
                auto* noFree = new MessageDialog("All Book are given");
                noFree->exec();
                delete noFree;
            }

            else
            {
                qDebug("Book %s %s is given to Reader %s %s", title.toStdString().c_str(), author.toStdString().c_str(), name.toStdString().c_str(), family.toStdString().c_str());
                guy->startReading(std::make_shared<booksys::Book>(*book), end);
                auto* start = new MessageDialog("Book is given");
                start->exec();
                delete start;
            }
        }

        else
        {
            qDebug("The Book %s %s is not found (giveBook)", title.toStdString().c_str(), author.toStdString().c_str());
            auto* fail = new MessageDialog("Book is not found");
            fail->exec();
            delete fail;
        }
    }

    emit pressedGiveBook();
}

void MainWindow::MainWindow::getBookFromReader(QString&& name, QString&& family, QString&& title, QString&& author) noexcept
{
    const auto guy = readSys->find(name, family);

    if (guy == readSys->cend())
    {
        qDebug("Reader %s %s is not found (getBook)", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    else
    {
        const auto book = bookSys->find(title, author);

        if (book != bookSys->cend())
        {
            const auto search = guy->findBook(title, author);

            if (search == guy->crend())
            {
                qDebug("The Book %s %s is not found (getBook)", title.toStdString().c_str(), author.toStdString().c_str());
                auto* notFound = new MessageDialog("Book is not found");
                notFound->exec();
                delete notFound;
            }

            else
            {
                if (!search->get()->isUse())
                {
                    qDebug("Book %s %s is not used (getBook)", title.toStdString().c_str(), author.toStdString().c_str());
                    auto* notUsed = new MessageDialog("The book is not used");
                    notUsed->exec();
                    delete notUsed;
                }

                else
                {
                    const auto check = search->get()->getLastReader()->first;

                    if (check->getName() != name || check->getFamily() != family)
                    {
                        qDebug("(Searchable Reader) %s %s != %s %s (Real Reader)",
                               name.toStdString().c_str(), family.toStdString().c_str(),
                               check->getName().toStdString().c_str(), check->getFamily().toStdString().c_str());
                        auto* notHim = new MessageDialog("Wrong reader");
                        notHim->exec();
                        delete notHim;
                    }

                    else
                    {
                        qDebug("Book %s %s is return by Reader %s %s", title.toStdString().c_str(), author.toStdString().c_str(), name.toStdString().c_str(), family.toStdString().c_str());
                        search->get()->finishReading(check);
                        auto* finish = new MessageDialog("Book is returned");
                        finish->exec();
                        delete finish;
                    }
                }
            }
        }

        else
        {
            qDebug("Book %s %s is not found (giveBook)", title.toStdString().c_str(), author.toStdString().c_str());
            auto* fail = new MessageDialog("Book is not found");
            fail->exec();
            delete fail;
        }
    }

    emit pressedGetBook();
}

void MainWindow::MainWindow::getBookFromReader(const QString& name, const QString& family, const QString& title, const QString& author) noexcept
{
    const auto guy = readSys->find(name, family);

    if (guy == readSys->cend())
    {
        qDebug("The Book %s %s is not found (getBook)", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }

    else
    {
        const auto book = bookSys->find(title, author);

        if (book != bookSys->cend())
        {
            const auto search = guy->findBook(title, author);

            if (search == guy->crend())
            {
                qDebug("The Book %s %s is not found (getBook)", title.toStdString().c_str(), author.toStdString().c_str());
                auto* notFound = new MessageDialog("Reader is not found");
                notFound->exec();
                delete notFound;
            }

            else
            {
                if (!search->get()->isUse())
                {
                    qDebug("Book %s %s is not used (getBook)", title.toStdString().c_str(), author.toStdString().c_str());
                    auto* notUsed = new MessageDialog("The book is not used");
                    notUsed->exec();
                    delete notUsed;
                }

                else
                {
                    const auto check = search->get()->getLastReader()->first;

                    if (check->getName() != name || check->getFamily() != family)
                    {
                        qDebug("(Searchable Reader) %s %s != %s %s (Real Reader)",
                               name.toStdString().c_str(), family.toStdString().c_str(),
                               check->getName().toStdString().c_str(), check->getFamily().toStdString().c_str());
                        auto* notHim = new MessageDialog("Wrong reader");
                        notHim->exec();
                        delete notHim;
                    }

                    else
                    {
                        qDebug("Book %s %s is return by Reader %s %s", title.toStdString().c_str(), author.toStdString().c_str(), name.toStdString().c_str(), family.toStdString().c_str());
                        search->get()->finishReading(check);
                        auto* finish = new MessageDialog("Book is returned");
                        finish->exec();
                        delete finish;
                    }
                }
            }
        }

        else
        {
            qDebug("Book %s %s is not found (giveBook)", title.toStdString().c_str(), author.toStdString().c_str());
            auto* fail = new MessageDialog("Book is not found");
            fail->exec();
            delete fail;
        }
    }

    emit pressedGetBook();
}

void MainWindow::addSimpleBook(QString&& title, QString&& author, const std::size_t ind = 1) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        for (std::size_t i = 0; i < ind; i++)
            theBook->addBook();

        qDebug("Books %s %s are added number %zu", title.toStdString().c_str(), author.toStdString().c_str(), ind);
        auto* succes = new MessageDialog("Succesfully added");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::addSimpleBook(const QString& title, const QString& author, const std::size_t ind = 1) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        for (std::size_t i = 0; i < ind; i++)
            theBook->addBook();

        qDebug("Books %s %s are added № %zu", title.toStdString().c_str(), author.toStdString().c_str(), ind);
        auto* succes = new MessageDialog("Succesfully added");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::removeSimpleBook(QString&& title, QString&& author, const std::size_t ind) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        qDebug("Book %s %s № %zu is removed", title.toStdString().c_str(), author.toStdString().c_str(), ind);
        theBook->removeBook(ind - 1);
        auto* succes = new MessageDialog("Book is removed");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::removeSimpleBook(const QString& title, const QString& author, const std::size_t ind) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        qDebug("Book %s %s № %zu is removed", title.toStdString().c_str(), author.toStdString().c_str(), ind);
        theBook->removeBook(ind - 1);
        auto* succes = new MessageDialog("Book is removed");
        succes->exec();
        delete succes;
    }

    else
    {
        qDebug("Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeTitle(QString&& title, QString&& author, QString&& newTitle) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        if (bookSys->find(newTitle, author) != bookSys->cend())
        {
            qDebug("The Book %s %s is already exists", newTitle.toStdString().c_str(), author.toStdString().c_str());
            auto* fail = new MessageDialog("Book is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("The Book %s %s is changing title", title.toStdString().c_str(), author.toStdString().c_str());
            theBook->changeTitle(newTitle);
            auto* succes = new MessageDialog("Title changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("The Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeTitle(const QString& title, const QString& author, const QString& newTitle) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        if (bookSys->find(newTitle, author) != bookSys->cend())
        {
            qDebug("The Book %s %s is already exists", newTitle.toStdString().c_str(), author.toStdString().c_str());
            auto* fail = new MessageDialog("Book is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("The Book %s %s is changing title", title.toStdString().c_str(), author.toStdString().c_str());
            theBook->changeTitle(newTitle);
            auto* succes = new MessageDialog("Title changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("The Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeAuthor(QString&& title, QString&& author, QString&& newAuthor) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        if (bookSys->find(title, newAuthor) != bookSys->cend())
        {
            qDebug("The Book %s %s is already exists", title.toStdString().c_str(), newAuthor.toStdString().c_str());
            auto* fail = new MessageDialog("Book is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("The Book %s %s is changing author", title.toStdString().c_str(), author.toStdString().c_str());
            theBook->changeAuthor(newAuthor);
            auto* succes = new MessageDialog("Author changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("The Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeAuthor(const QString& title, const QString& author, const QString& newAuthor) noexcept
{
    const auto theBook = bookSys->find(title, author);

    if (theBook != bookSys->cend())
    {
        if (bookSys->find(title, newAuthor) != bookSys->cend())
        {
            qDebug("The Book %s %s is already exists", title.toStdString().c_str(), newAuthor.toStdString().c_str());
            auto* fail = new MessageDialog("Book is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("The Book %s %s is changing author", title.toStdString().c_str(), author.toStdString().c_str());
            theBook->changeAuthor(newAuthor);
            auto* succes = new MessageDialog("Author changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("The Book %s %s is not found", title.toStdString().c_str(), author.toStdString().c_str());
        auto* fail = new MessageDialog("Book is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeName(QString&& name, QString&& family, QString&& newName) noexcept
{
    const auto reader = readSys->find(name, family);

    if (reader != readSys->cend())
    {
        if (readSys->find(newName, family) != readSys->cend())
        {
            qDebug("Reader %s %s is already exists", newName.toStdString().c_str(), family.toStdString().c_str());
            auto* fail = new MessageDialog("Reader is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("Reader %s %s is changing name", name.toStdString().c_str(), family.toStdString().c_str());
            reader->changeName(newName);
            auto* succes = new MessageDialog("Name changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("Reader %s %s is not found", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeName(const QString& name, const QString& family, const QString& newName) noexcept
{
    const auto reader = readSys->find(name, family);

    if (reader != readSys->cend())
    {
        if (readSys->find(newName, family) != readSys->cend())
        {
            qDebug("Reader %s %s is already exists", newName.toStdString().c_str(), family.toStdString().c_str());
            auto* fail = new MessageDialog("Reader is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("Reader %s %s is changing name", name.toStdString().c_str(), family.toStdString().c_str());
            reader->changeName(newName);
            auto* succes = new MessageDialog("Name changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("Reader %s %s is not found", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeFamily(QString&& name, QString&& family, QString&& newFamily) noexcept
{
    const auto reader = readSys->find(name, family);

    if (reader != readSys->cend())
    {
        if (readSys->find(name, newFamily) != readSys->cend())
        {
            qDebug("Reader %s %s is already exists", name.toStdString().c_str(), newFamily.toStdString().c_str());
            auto* fail = new MessageDialog("Reader is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("Reader %s %s is changing name", name.toStdString().c_str(), family.toStdString().c_str());
            reader->changeName(newFamily);
            auto* succes = new MessageDialog("Name changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("Reader %s %s is not found", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }
}

void MainWindow::changeFamily(const QString& name, const QString& family, const QString& newFamily) noexcept
{
    const auto reader = readSys->find(name, family);

    if (reader != readSys->cend())
    {
        if (readSys->find(name, newFamily) != readSys->cend())
        {
            qDebug("Reader %s %s is already exists", name.toStdString().c_str(), newFamily.toStdString().c_str());
            auto* fail = new MessageDialog("Reader is already exist");
            fail->exec();
            delete fail;
        }

        else
        {
            qDebug("Reader %s %s is changing name", name.toStdString().c_str(), family.toStdString().c_str());
            reader->changeName(newFamily);
            auto* succes = new MessageDialog("Name changed");
            succes->exec();
            delete succes;
        }
    }

    else
    {
        qDebug("Reader %s %s is not found", name.toStdString().c_str(), family.toStdString().c_str());
        auto* fail = new MessageDialog("Reader is not found");
        fail->exec();
        delete fail;
    }
}
