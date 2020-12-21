#include <debug.h>

#ifdef RELEASE
#undef DEBUG
#endif

#include "book.h"
#include "reader.h"
#include "messagedialog.h"

#include <memory>
#include <tuple>
#include <chrono>
#include <ctime>

std::shared_ptr<booksys::BookSystem> booksys::BookSystem::instance_;

std::shared_ptr<booksys::Book> booksys::BookSystem::getUnused(QString&& title, QString&& author) noexcept
{
    for (auto theBook : books_)
    {
        if (theBook->title_ == title && theBook->author_ == author)
        {
            for (auto book : theBook->books_)
                if (!book->isUse())
                    return book;

            auto* fail = new MessageDialog("All book are in use");
            fail->exec();
            delete fail;
            return nullptr;
        }
    }

    auto* fail = new MessageDialog("All book are in use");
    fail->exec();
    delete fail;
    return nullptr;
}

std::shared_ptr<booksys::Book> booksys::BookSystem::getUnused(const QString& title, const QString& author) noexcept
{
    for (auto theBook : books_)
    {
        if (theBook->title_ == title && theBook->author_ == author)
        {
            for (auto book : theBook->books_)
                if (!book->isUse())
                    return book;

            auto* fail = new MessageDialog("All book are in use");
            fail->exec();
            delete fail;
            return nullptr;
        }
    }

    auto* fail = new MessageDialog("All book are in use");
    fail->exec();
    delete fail;
    return nullptr;
}

std::shared_ptr<booksys::BookSystem> booksys::BookSystem::getInstance() noexcept
{
    if (!instance_)
        instance_ = std::make_shared<BookSystem>();
    return instance_;
}

QVector<std::shared_ptr<booksys::TheBook>>::iterator booksys::BookSystem::find(std::shared_ptr<booksys::TheBook> theBook) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (**it == *theBook)
            return it;

    return books_.end();
}

QVector<std::shared_ptr<booksys::TheBook>>::iterator booksys::BookSystem::find(QString&& title, QString&& author) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (it->get()->title_ == title && it->get()->author_ == author)
            return it;

    return books_.end();
}

QVector<std::shared_ptr<booksys::TheBook>>::iterator booksys::BookSystem::find(const QString& title, const QString& author) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (it->get()->title_ == title && it->get()->author_ == author)
            return it;

    return books_.end();
}

bool booksys::BookSystem::addBook(std::shared_ptr<booksys::TheBook> theBook) noexcept
{
    const auto search = find(theBook);

    if (search == books_.end())
    {
        books_.push_back(theBook);
        return true;
    }

    return false;
}

bool booksys::BookSystem::addBook(QString&& title, QString&& author) noexcept
{
    const auto search = find(title, author);

    if (search == books_.end())
    {
        books_.push_back(std::make_shared<TheBook>(title, author));
        books_.back()->books_.push_back(std::make_shared<Book>(title, author));
        return true;
    }

    return false;
}

bool booksys::BookSystem::addBook(const QString& title, const QString& author) noexcept
{
    const auto search = find(title, author);

    if (search == books_.end())
    {
        books_.push_back(std::make_shared<TheBook>(title, author));
        books_.back()->books_.push_back(std::make_shared<Book>(title, author));
        return true;
    }

    return false;
}

bool booksys::BookSystem::removeBook(std::shared_ptr<booksys::TheBook> theBook) noexcept
{
    const auto search = find(theBook);

    if (search != books_.end())
    {
        books_.erase(search);
        return true;
    }

    return false;
}

bool booksys::BookSystem::removeBook(QString&& title, QString&& author) noexcept
{
    const auto search = find(title, author);

    if (search != books_.end())
    {
        books_.erase(search);
        return true;
    }

    return false;
}

bool booksys::BookSystem::removeBook(const QString& title, const QString& author) noexcept
{
    const auto search = find(title, author);

    if (search != books_.end())
    {
        books_.erase(search);
        return true;
    }

    return false;
}

void booksys::Book::startReading(std::shared_ptr<read::Reader> reader, booksys::date finishDate) noexcept
{
    #ifdef DEBUG
    qDebug("Reader pointer %p (start reading from Book)", reader.get());
    #endif

    const auto start    = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto now      = *std::localtime(&start);

    readers_.push_back(std::make_pair(reader,
                          std::make_pair(std::make_tuple(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900),
                                         finishDate)));
    #ifdef DEBUG
    qDebug("Reader pointer after add to readers %p (start reading from Book)", readers_.back().first.get());
    #endif

    isUsing_ = true;
}

void booksys::Book::finishReading(std::shared_ptr<read::Reader> reader) noexcept
{
    const auto finish   = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto now      = *std::localtime(&finish);

    if (*readers_.back().first != *reader)
    {
        auto* fail = new MessageDialog("Wrong reader");
        fail->exec();
        delete fail;
    }

    else
    {
        isUsing_ = false;

        if (std::get<2>(readers_.back().second.second) > now.tm_year + 1900)
        {
            auto* late = new MessageDialog("Reader is late");
            late->exec();
            delete late;
        }

        else if (std::get<1>(readers_.back().second.second) > now.tm_mon + 1)
        {
            auto* late = new MessageDialog("Reader is late");
            late->exec();
            delete late;
        }

        else if (std::get<0>(readers_.back().second.second) > now.tm_mday)
        {
            auto* late = new MessageDialog("Reader is late");
            late->exec();
            delete late;
        }

        readers_.back().second.second = std::make_tuple(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
    }
}

QVector<std::shared_ptr<booksys::Book>>::iterator booksys::TheBook::getUnused() noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (!it->get()->isUse())
            return it;

    return books_.begin();
}

void booksys::TheBook::changeTitle(QString&& title) noexcept
{
    title_ = title;
    std::for_each(books_.begin(), books_.end(),
                  [&title] (std::shared_ptr<booksys::Book> b) { b->changeTitle(title); });
}

void booksys::TheBook::changeTitle(const QString& title) noexcept
{
    title_ = title;
    std::for_each(books_.begin(), books_.end(),
                  [&title] (std::shared_ptr<booksys::Book> b) { b->changeTitle(title); });
}

void booksys::TheBook::changeAuthor(QString&& author) noexcept
{
    author_ = author;
    std::for_each(books_.begin(), books_.end(),
                  [&author] (std::shared_ptr<booksys::Book> b) { b->changeAuthor(author); });
}

void booksys::TheBook::changeAuthor(const QString& author) noexcept
{
    author_ = author;
    std::for_each(books_.begin(), books_.end(),
                  [&author] (std::shared_ptr<booksys::Book> b) { b->changeAuthor(author); });
}
