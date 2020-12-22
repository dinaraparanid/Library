#include "information.h"
#include <QFont>

TheBookInformation::TheBookInformation(QString&& title, QString&& bookTitle,
                                       QString&& bookAuthor, const std::size_t booksAmount) noexcept :
    title_(title),
    ok_(new QPushButton("OK", this)),
    bookTitle_("Book Title: " + bookTitle, this),
    bookAuthor_("Book Author: " + bookAuthor, this),
    booksAmount_("Book Amount: " + QString::fromStdString(std::to_string(booksAmount)), this)

{
    setGeometry(500, 500, 500, 200);
    setFixedSize(size());
    setWindowTitle(title);

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

TheBookInformation::TheBookInformation(const QString& title, const QString& bookTitle,
                                       const QString& bookAuthor, const std::size_t booksAmount) noexcept :
    title_(title),
    ok_(new QPushButton("OK", this)),
    bookTitle_("Book Title: " + bookTitle, this),
    bookAuthor_("Book Author: " + bookAuthor, this),
    booksAmount_("Book Amount: " + QString::fromStdString(std::to_string(booksAmount)), this)

{
    setGeometry(500, 500, 500, 200);
    setFixedSize(size());
    setWindowTitle(title);

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
