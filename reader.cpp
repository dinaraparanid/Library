#include <debug.h>

#include "reader.h"

std::shared_ptr<read::ReaderBase>read::ReaderBase::instance_;

std::shared_ptr<read::ReaderBase> read::ReaderBase::getInstance() noexcept
{
    if (!instance_)
        instance_ = std::make_shared<ReaderBase>();
    return instance_;
}

QVector<std::shared_ptr<read::Reader>>::iterator read::ReaderBase::find(std::shared_ptr<read::Reader> reader) noexcept
{    
    for (auto it = readers_.begin(); it != readers_.end(); ++it)
        if (*it == reader)
            return it;

    return readers_.end();
}

QVector<std::shared_ptr<read::Reader>>::iterator read::ReaderBase::find(QString&& name, QString&& family) noexcept
{
    #ifdef DEBUG
    if (!readers_.empty())
        qDebug("Last reader %p", readers_.back().get());
    #endif

    for (auto it = readers_.begin(); it != readers_.end(); ++it)
    {
        if (it->get()->name_ == name && it->get()->family_ == family)
        {
            #ifdef DEBUG
            qDebug("find readerd by str from ReaderBase %p", it->get());
            #endif

            return it;
        }
    }

    return readers_.end();
}

QVector<std::shared_ptr<read::Reader>>::iterator read::ReaderBase::find(const QString& name, const QString& family) noexcept
{
    #ifdef DEBUG
    if (!readers_.empty())
        qDebug("Last reader %p", readers_.back().get());
    #endif

    for (auto it = readers_.begin(); it != readers_.end(); ++it)
    {
        if (it->get()->name_ == name && it->get()->family_ == family)
        {
            #ifdef DEBUG
            qDebug("find readerd by str from ReaderBase %p", it->get());
            #endif

            return it;
        }
    }

    return readers_.end();
}

bool read::ReaderBase::addReader(std::shared_ptr<read::Reader> reader) noexcept
{
    #ifdef DEBUG
    qDebug("Add readerd by ptr from ReaderBase %p", reader.get());
    #endif

    const auto search = find(reader);

    if (search == readers_.end())
    {
        readers_.push_back(reader);
        return true;
    }

    return false;
}

bool read::ReaderBase::addReader(QString&& name, QString&& family) noexcept
{
    const auto search = find(name, family);

    if (search == readers_.end())
    {
        auto reader = std::make_shared<read::Reader>(name, family);
        #ifdef DEBUG
        qDebug("Add readerd by str from ReaderBase %p", reader.get());
        #endif
        readers_.push_back(reader);
        return true;
    }

    return false;
}

bool read::ReaderBase::addReader(const QString& name, const QString& family) noexcept
{
    const auto search = find(name, family);

    if (search == readers_.end())
    {
        auto reader = std::make_shared<read::Reader>(name, family);
        #ifdef DEBUG
        qDebug("Add readerd by str from ReaderBase %p", reader.get());
        #endif
        readers_.push_back(reader);
        return true;
    }

    return false;
}

bool read::ReaderBase::removeReader(std::shared_ptr<read::Reader> reader) noexcept
{
    const auto search = find(reader);

    if (search != readers_.end())
    {
        search->get()->removeAllBooks();
        readers_.erase(search);
        return true;
    }

    return false;
}

bool read::ReaderBase::removeReader(QString&& name, QString&& family) noexcept
{
    const auto search = find(name, family);

    if (search != readers_.end())
    {
        search->get()->removeAllBooks();
        readers_.erase(search);
        return true;
    }

    return false;
}

bool read::ReaderBase::removeReader(const QString& name, const QString& family) noexcept
{
    const auto search = find(name, family);

    if (search != readers_.end())
    {
        search->get()->removeAllBooks();
        readers_.erase(search);
        return true;
    }

    return false;
}

QVector<std::weak_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(std::weak_ptr<booksys::Book> book)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
    {
        #ifdef DEBUG
        qDebug("Reader findBook %s %s %p", it->lock()->title_.toStdString().c_str(), it->lock()->author_.toStdString().c_str(), it->lock().get());
        #endif

        if (it->lock()->title_ == book.lock()->title_ && it->lock()->author_ == book.lock()->author_)
            return it;
    }

    return books_.rend();
}

QVector<std::weak_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(QString&& title, QString&& author)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
    {
        #ifdef DEBUG
        qDebug("Reader findBook %s %s %p", it->lock()->title_.toStdString().c_str(), it->lock()->author_.toStdString().c_str(), it->lock().get());
        #endif

        if (it->lock()->title_ == title && it->lock()->author_ == author)
            return it;
    }

    return books_.rend();
}

QVector<std::weak_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(const QString& title, const QString& author)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
    {
        #ifdef DEBUG
        qDebug("Reader findBook %s %s %p", it->lock()->title_.toStdString().c_str(), it->lock()->author_.toStdString().c_str(), it->lock().get());
        #endif

        if (it->lock()->title_ == title && it->lock()->author_ == author)
            return it;
    }

    return books_.rend();
}

void read::Reader::startReading(std::weak_ptr<booksys::Book> book) noexcept
{
    books_.push_back(book);

    #ifdef DEBUG
    qDebug("reader start reading %s %s %p", book.lock()->title_.toStdString().c_str(), book.lock()->author_.toStdString().c_str(), book.lock().get());
    #endif
}

void read::Reader::removeBook(std::weak_ptr<booksys::Book> book) noexcept
{
    book.lock()->removeReader(name_, family_);
    books_.erase(findBook(book).base());
}

void read::Reader::removeBook(QString&& name, QString&& family) noexcept
{
    auto book = findBook(name, family);
    book->lock()->removeReader(name_, family_);
}

void read::Reader::removeBook(const QString& name, const QString& family) noexcept
{
    auto book = findBook(name, family);

    #ifdef DEBUG
    qDebug("Reader remove book %s %s", book->lock()->title_.toStdString().c_str(), book->lock()->author_.toStdString().c_str());
    #endif

    book->lock()->removeReader(name_, family_);
}

void read::Reader::removeAllBooks() noexcept
{
    for (auto book : books_)
        qDebug() << book.lock()->title_ << " " << book.lock()->author_;

    while (!books_.empty())
    {
        removeBook(books_[0].lock()->title_, books_[0].lock()->author_);
        books_.pop_front();
    }
}
