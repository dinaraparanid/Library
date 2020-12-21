#include <debug.h>

#ifdef RELEASE
#undef DEBUG
#endif

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
        readers_.erase(search);
        return true;
    }

    return false;
}

QVector<std::shared_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(QString&& title, QString&& author)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
    {
        #ifdef DEBUG
        qDebug("Reader findBook %s %s %p", it->get()->title_.toStdString().c_str(), it->get()->author_.toStdString().c_str(), it->get());
        #endif

        if (it->get()->title_ == title && it->get()->author_ == author)
            return it;
    }

    return books_.rend();
}

QVector<std::shared_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(const QString& title, const QString& author)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
    {
        #ifdef DEBUG
        qDebug("Reader findBook %s %s %p", it->get()->title_.toStdString().c_str(), it->get()->author_.toStdString().c_str(), it->get());
        #endif

        if (it->get()->title_ == title && it->get()->author_ == author)
            return it;
    }

    return books_.rend();
}

void read::Reader::startReading(std::shared_ptr<booksys::Book> book) noexcept
{
    books_.push_back(book);

#ifdef DEBUG
    qDebug("reader start reading %s %s %p", book->title_.toStdString().c_str(), book->author_.toStdString().c_str(), book.get());
#endif
}
