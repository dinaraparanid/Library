#include "information.h"
#include "messagedialog.h"

#include <QFont>

info::TheBookInformation::TheBookInformation(QString&& bookTitle, QString&& bookAuthor, const std::size_t booksAmount) noexcept :
    ok_(new QPushButton("OK", this)),
    bookTitle_("Book Title: " + bookTitle, this),
    bookAuthor_("Book Author: " + bookAuthor, this),
    booksAmount_("Book Amount: " + QString::fromStdString(std::to_string(booksAmount)), this)

{
    setGeometry(500, 500, 500, 200);
    setFixedSize(size());
    setWindowTitle(bookTitle + " " + bookAuthor);

    ok_->setGeometry(400, 150, 75, 25);

    const QFont font("Calibri", 18, 3, true);

    bookTitle_.setFont(font);
    bookAuthor_.setFont(font);
    booksAmount_.setFont(font);

    bookTitle_.setGeometry(100, 10, 300, 50);
    bookAuthor_.setGeometry(100, 60, 300, 50);
    booksAmount_.setGeometry(100, 110, 300, 50);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}

info::TheBookInformation::TheBookInformation(const QString& bookTitle, const QString& bookAuthor, const std::size_t booksAmount) noexcept :
    ok_(new QPushButton("OK", this)),
    bookTitle_("Book Title: " + bookTitle, this),
    bookAuthor_("Book Author: " + bookAuthor, this),
    booksAmount_("Book Amount: " + QString::fromStdString(std::to_string(booksAmount)), this)

{
    setGeometry(500, 500, 500, 200);
    setFixedSize(size());
    setWindowTitle(bookTitle + " " + bookAuthor);

    ok_->setGeometry(400, 150, 75, 25);

    const QFont font("Calibri", 18, 3, true);

    bookTitle_.setFont(font);
    bookAuthor_.setFont(font);
    booksAmount_.setFont(font);

    bookTitle_.setGeometry(100, 10, 300, 50);
    bookAuthor_.setGeometry(100, 60, 300, 50);
    booksAmount_.setGeometry(100, 110, 300, 50);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}

info::ReaderInformation::ReaderInformation(QString&& name, QString&& family) noexcept :
    ok_(new QPushButton("OK", this))
{
    setGeometry(500, 500, 500, 700);
    setFixedSize(size());
    setWindowTitle(name + " " + family);

    ok_->setGeometry(0, 0, 100, 100);

    const auto guy = read::ReaderBase::getInstance()->find(name, family);

    if (guy != read::ReaderBase::getInstance()->cend())
    {
        for (auto book : guy->get()->books_)
            addItem("Title: " + book.lock()->getTitle() + " Author: " + book.lock()->getAuthor());

        setFont(QFont("Calibri Light", 12, 3, true));
    }

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}

info::ReaderInformation::ReaderInformation(const QString& name, const QString& family) noexcept :
    ok_(new QPushButton("OK", this))
{
    setGeometry(500, 500, 500, 700);
    setFixedSize(size());
    setWindowTitle(name + " " + family);

    ok_->setGeometry(0, 0, 100, 100);

    const auto guy = read::ReaderBase::getInstance()->find(name, family);

    if (guy != read::ReaderBase::getInstance()->cend())
    {
        for (auto book : guy->get()->books_)
            addItem("Title: " + book.lock()->getTitle() + " Author: " + book.lock()->getAuthor());

        setFont(QFont("Calibri Light", 12, 3, true));
    }

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}

info::ReaderInformation::ReaderInformation(std::shared_ptr<read::Reader> reader) noexcept :
    ok_(new QPushButton("OK", this))
{
    setGeometry(500, 200, 500, 700);
    setFixedSize(size());
    setWindowTitle(reader->name_ + " " + reader->family_);

    ok_->setGeometry(400, 650, 75, 25);

    for (auto book : reader->books_)
        addItem("Title: " + book.lock()->getTitle() + " Author: " + book.lock()->getAuthor());

    setFont(QFont("Calibri Light", 15, 3, true));

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}
