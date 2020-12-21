#ifndef READER_H
#define READER_H

#include <debug.h>

#ifdef RELEASE
#undef DEBUG
#endif

#include <memory>

#include <QVector>
#include <QString>

#include "book.h"

namespace read
{
    class Reader : std::enable_shared_from_this<Reader> // just 1 man
    {
        friend class ReaderBase;

        QString name_;
        QString family_;
        QVector<std::shared_ptr<booksys::Book>> books_; // books he've read

    public:

        Reader(QString&& name, QString&& family)                noexcept : name_(name), family_(family) {}
        Reader(const QString& name, const QString& family)      noexcept : name_(name), family_(family) {}
        ~Reader() = default;

        [[nodiscard]] bool late()                                   noexcept { return *books_.back()->readers_.back().first == *this && books_.back()->isUse(); }
        [[nodiscard]] bool operator==(const Reader& reader)   const noexcept { return name_ == reader.name_ && family_ == reader.family_; }
        [[nodiscard]] bool operator!=(const Reader& reader)   const noexcept { return !(*this == reader); }

        [[nodiscard]] QString getName()                       const noexcept { return name_; }
        [[nodiscard]] QString getFamily()                     const noexcept { return family_; }

        [[nodiscard]] QVector<std::shared_ptr<booksys::Book>>::reverse_iterator findBook(QString&&, QString&&)              noexcept;
        [[nodiscard]] QVector<std::shared_ptr<booksys::Book>>::reverse_iterator findBook(const QString&, const QString&)    noexcept;
        [[nodiscard]] QVector<std::shared_ptr<booksys::Book>>::const_reverse_iterator crend() const noexcept { return books_.crend(); }

        void startReading(std::shared_ptr<booksys::Book> book)  noexcept;
        void changeName(QString&& name)                         noexcept { name_ = name; }
        void changeName(const QString& name)                    noexcept { name_ = name; }
        void changeFamily(QString&& family)                     noexcept { family_ = family; }
        void changeFamily(const QString& family)                noexcept { family_ = family; }
    };

    class ReaderBase
    {
        QVector<std::shared_ptr<Reader>> readers_;
        static std::shared_ptr<ReaderBase> instance_;

    public:
        ReaderBase()                                = default;
        ReaderBase(const ReaderBase&)               = delete;
        ReaderBase(ReaderBase&&)                    = delete;
        ReaderBase& operator= (const ReaderBase&)   = delete;
        ReaderBase& operator= (ReaderBase&&)        = delete;
        ~ReaderBase()                               = default;

        [[nodiscard]] bool removeReader(std::shared_ptr<Reader>)                      noexcept;
        [[nodiscard]] bool removeReader(QString&&, QString&&)                         noexcept;
        [[nodiscard]] bool removeReader(const QString&, const QString&)               noexcept;

        [[nodiscard]] static std::shared_ptr<ReaderBase> getInstance()                noexcept;

        [[nodiscard]] bool addReader(std::shared_ptr<Reader>)                         noexcept;
        [[nodiscard]] bool addReader(QString&&, QString&&)                            noexcept;
        [[nodiscard]] bool addReader(const QString&, const QString&)                  noexcept;

        [[nodiscard]] QVector<std::shared_ptr<Reader>>::iterator find(std::shared_ptr<Reader>)         noexcept;
        [[nodiscard]] QVector<std::shared_ptr<Reader>>::iterator find(QString&&, QString&&)            noexcept;
        [[nodiscard]] QVector<std::shared_ptr<Reader>>::iterator find(const QString&, const QString&)  noexcept;
        [[nodiscard]] QVector<std::shared_ptr<Reader>>::const_iterator cend()                    const noexcept { return readers_.cend(); }
    };
}

#endif // READER_H
