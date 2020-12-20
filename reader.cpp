#include "reader.h"

std::shared_ptr<read::ReaderBase>read::ReaderBase::instance_;

std::shared_ptr<read::ReaderBase> read::ReaderBase::getInstance() noexcept
{
    if (!instance_)
        instance_ = std::make_shared<ReaderBase>();
    return instance_;
}

QVector<read::Reader>::iterator read::ReaderBase::find(Reader&& reader) noexcept
{
    for (auto it = readers_.begin(); it != readers_.end(); ++it)
        if (*it == reader)
            return it;

    return readers_.end();
}

QVector<read::Reader>::iterator read::ReaderBase::find(const Reader& reader) noexcept
{
    for (auto it = readers_.begin(); it != readers_.end(); ++it)
        if (*it == reader)
            return it;

    return readers_.end();
}

QVector<read::Reader>::iterator read::ReaderBase::find(QString&& name, QString&& family) noexcept
{
    for (auto it = readers_.begin(); it != readers_.end(); ++it)
        if (it->name_ == name && it->family_ == family)
            return it;

    return readers_.end();
}

QVector<read::Reader>::iterator read::ReaderBase::find(const QString& name, const QString& family) noexcept
{
    for (auto it = readers_.begin(); it != readers_.end(); ++it)
        if (it->name_ == name && it->family_ == family)
            return it;

    return readers_.end();
}

bool read::ReaderBase::addReader(Reader&& reader) noexcept
{
    const auto search = find(reader);

    if (search == readers_.end())
    {
        readers_.push_back(reader);
        return true;
    }

    return false;
}

bool read::ReaderBase::addReader(const Reader& reader) noexcept
{
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
        readers_.push_back(Reader(name, family));
        return true;
    }

    return false;
}

bool read::ReaderBase::addReader(const QString& name, const QString& family) noexcept
{
    const auto search = find(name, family);

    if (search == readers_.end())
    {
        readers_.push_back(Reader(name, family));
        return true;
    }

    return false;
}

bool read::ReaderBase::removeReader(Reader&& reader) noexcept
{
    const auto search = find(reader);

    if (search != readers_.end())
    {
        readers_.erase(search);
        return true;
    }

    return false;
}

bool read::ReaderBase::removeReader(const Reader& reader) noexcept
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

void read::Reader::startReading(std::shared_ptr<booksys::Book> book, booksys::date end) noexcept
{
    books_.push_back(book);
    book->startReading(std::make_shared<read::Reader>(*this), end);
}

QVector<std::shared_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(QString&& title, QString&& author)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
        if (it->get()->title_ == title && it->get()->author_ == author)
            return it;

    return books_.rend();
}

QVector<std::shared_ptr<booksys::Book>>::reverse_iterator read::Reader::findBook(const QString& title, const QString& author)  noexcept
{
    for (auto it = books_.rbegin(); it != books_.rend(); ++it)
        if (it->get()->title_ == title && it->get()->author_ == author)
            return it;

    return books_.rend();
}
