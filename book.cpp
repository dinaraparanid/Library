#include "book.h"
#include "reader.h"
#include "messagedialog.h"

#include <memory>
#include <tuple>
#include <chrono>
#include <ctime>

std::shared_ptr<booksys::BookSystem> booksys::BookSystem::instance_;

booksys::Book* booksys::BookSystem::getUnused(QString&& title, QString&& author) noexcept
{
    for (auto theBook : books_)
    {
        if (theBook.title_ == title && theBook.author_ == author)
        {
            for (auto book : theBook.books_)
                if (!book.isUse())
                    return &book;

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

booksys::Book* booksys::BookSystem::getUnused(const QString& title, const QString& author) noexcept
{
    for (auto theBook : books_)
    {
        if (theBook.title_ == title && theBook.author_ == author)
        {
            for (auto book : theBook.books_)
                if (!book.isUse())
                    return &book;

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

QVector<booksys::TheBook>::iterator booksys::BookSystem::find(TheBook&& theBook) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (*it == theBook)
            return it;

    return books_.end();
}

QVector<booksys::TheBook>::iterator booksys::BookSystem::find(const TheBook& theBook) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (*it == theBook)
            return it;

    return books_.end();
}

QVector<booksys::TheBook>::iterator booksys::BookSystem::find(QString&& title, QString&& author) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (it->title_ == title && it->author_ == author)
            return it;

    return books_.end();
}

QVector<booksys::TheBook>::iterator booksys::BookSystem::find(const QString& title, const QString& author) noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (it->title_ == title && it->author_ == author)
            return it;

    return books_.end();
}

bool booksys::BookSystem::addBook(TheBook&& theBook) noexcept
{
    const auto search = find(theBook);

    if (search == books_.end())
    {
        books_.push_back(theBook);
        return true;
    }

    return false;
}

bool booksys::BookSystem::addBook(const TheBook& theBook) noexcept
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
    const TheBook theBook(title, author);
    const auto search = find(theBook);

    if (search == books_.end())
    {
        books_.push_back(theBook);
        books_.back().books_.push_back(Book(title, author));
        return true;
    }

    return false;
}

bool booksys::BookSystem::addBook(const QString& title, const QString& author) noexcept
{
    const TheBook theBook(title, author);
    const auto search = find(theBook);

    if (search == books_.end())
    {
        books_.push_back(theBook);
        books_.back().books_.push_back(Book(title, author));
        return true;
    }

    return false;
}

bool booksys::BookSystem::removeBook(TheBook&& theBook) noexcept
{
    const auto search = find(theBook);

    if (search != books_.end())
    {
        books_.erase(search);
        return true;
    }

    return false;
}

bool booksys::BookSystem::removeBook(const TheBook& theBook) noexcept
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

void booksys::Book::startReading(const std::shared_ptr<read::Reader> reader, booksys::date finishDate) noexcept
{
    const auto start    = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto now      = *std::localtime(&start);

    readers_.push_back(std::make_pair(reader,
                          std::make_pair(std::make_tuple(now.tm_mday, now.tm_mon, now.tm_year),
                                         finishDate)));

    isUsing_ = true;
}

void booksys::Book::finishReading(const std::shared_ptr<read::Reader> reader) noexcept
{
    const auto finish   = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto now      = *std::localtime(&finish);

    if (readers_.back().first != reader)
    {
        auto* fail = new MessageDialog("Wrong reader");
        fail->exec();
        delete fail;
    }

    else
    {
        isUsing_ = false;

        if (std::get<2>(readers_.back().second.second) > now.tm_year)
        {
            auto* late = new MessageDialog("Reader is late");
            late->exec();
            delete late;
        }

        else if (std::get<1>(readers_.back().second.second) > now.tm_mon)
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

        readers_.back().second.second = std::make_tuple(now.tm_mday, now.tm_mon, now.tm_year);
    }
}

QVector<booksys::Book>::iterator booksys::TheBook::getUnused() noexcept
{
    for (auto it = books_.begin(); it != books_.end(); ++it)
        if (!it->isUse())
            return it;

    return books_.begin();
}
