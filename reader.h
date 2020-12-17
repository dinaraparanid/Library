#ifndef READER_H
#define READER_H

#include <memory>

#include <QVector>
#include <QString>

#include "book.h"

namespace read
{
    class Reader // just 1 man
    {
        friend class ReaderBase;

        QString name_;
        QString family_;
        QVector<std::shared_ptr<booksys::Book>> books_; // books he've read

    public:

        Reader(QString&& name, QString&& family) noexcept : name_(name), family_(family) {}
        Reader(const QString& name, const QString& family) noexcept : name_(name), family_(family) {}
        ~Reader() = default;

        bool late() noexcept { return *books_.back()->readers_.back().first == *this && books_.back()->isUse(); }
        bool operator==(const Reader& reader) const noexcept { return name_ == reader.name_ && family_ == reader.family_; }
        bool operator!=(const Reader& reader) const noexcept { return !(*this == reader); }
        void finishReading() noexcept { books_.back()->finishReading(); }

        QString getName()   const noexcept { return name_; }
        QString getFamily() const noexcept { return family_; }

        void reading(std::shared_ptr<booksys::Book> book) noexcept { books_.push_back(book); }
        void changeName(QString&& name)                   noexcept { name_ = name; }
        void changeName(const QString& name)              noexcept { name_ = name; }
        void changeFamily(QString&& family)               noexcept { family_ = family; }
        void changeFamily(const QString& family)          noexcept { family_ = family; }
    };

    class ReaderBase
    {
        QVector<Reader> readers_;
        static std::shared_ptr<ReaderBase> instance_;

    public:
        ReaderBase() = default;
        ReaderBase(const ReaderBase&) = delete;
        ReaderBase(ReaderBase&&) = delete;
        ReaderBase& operator= (const ReaderBase&) = delete;
        ReaderBase& operator= (ReaderBase&&) = delete;
        ~ReaderBase() = default;

        bool removeReader(Reader&&)                                                noexcept;
        bool removeReader(const Reader&)                                           noexcept;
        bool removeReader(QString&& name, QString&& family)                        noexcept;
        bool removeReader(const QString& name, const QString& family)              noexcept;

        std::shared_ptr<ReaderBase> getInstance()                                  noexcept;

        bool addReader(Reader&&)                                                   noexcept;
        bool addReader(const Reader&)                                              noexcept;
        bool addReader(QString&& name, QString&& family)                           noexcept;
        bool addReader(const QString& name, const QString& family)                 noexcept;

        QVector<Reader>::iterator find(Reader&&)                                   noexcept;
        QVector<Reader>::iterator find(const Reader&)                              noexcept;
        QVector<Reader>::iterator find(QString&& name, QString&& family)           noexcept;
        QVector<Reader>::iterator find(const QString& name, const QString& family) noexcept;
    };
}

#endif // READER_H
