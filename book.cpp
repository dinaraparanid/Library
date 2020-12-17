#include "book.h"
#include "reader.h"

#include <memory>
#include <tuple>
#include <chrono>
#include <ctime>

std::shared_ptr<booksys::BookSystem> booksys::BookSystem::instance_;

booksys::Book& booksys::BookSystem::getUnused(const std::size_t ind)
{
    std::size_t index = 0;

    for (auto& the_book : books_)
    {
        for (auto& book : the_book.books_)
        {
            if (!book.isUse())
            {
                if (index == ind)
                    return book;

                index++;
                break;
            }
        }
    }

    throw std::logic_error("The book is not found");
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

bool booksys::BookSystem::addBook(QString&& title, QString&& author, QSet<QString>&& genres) noexcept
{
    const TheBook theBook(title, author, genres);
    const auto search = find(theBook);

    if (search == books_.end())
    {
        books_.push_back(theBook);
        return true;
    }

    return false;
}

bool booksys::BookSystem::addBook(const QString& title, const QString& author, const QSet<QString>& genres) noexcept
{
    const TheBook theBook(title, author, genres);
    const auto search = find(theBook);

    if (search == books_.end())
    {
        books_.push_back(theBook);
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

void booksys::Book::startReading(const std::shared_ptr<read::Reader>& reader, booksys::date finishDate) noexcept
{
    const auto start = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const std::tm now = *std::localtime(&start);

    readers_.push_back(std::make_pair(reader,
                          std::make_pair(std::make_tuple(now.tm_mday, now.tm_mon, now.tm_year),
                                         finishDate)));

    isUsing_ = true;
}

void booksys::Book::finishReading() noexcept
{
    const auto finish = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto now = *std::localtime(&finish);

    isUsing_ = false;
    readers_.back().second.second = std::make_tuple(now.tm_mday, now.tm_mon, now.tm_year);
}
