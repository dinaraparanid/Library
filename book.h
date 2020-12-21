#ifndef BOOK_H
#define BOOK_H

#include <debug.h>

#ifdef RELEASE
#undef DEBUG
#endif

#include <cstdint>
#include <memory>
#include <tuple>

#include <QVector>
#include <QString>
#include <QDebug>

#define __TRY__(FUNCTION)           \
try { FUNCTION; }                   \
catch (const std::logic_error& e)	\
{                                   \
    qDebug(e.what());               \
    std::terminate();               \
}

namespace read { class Reader; }

namespace booksys
{
    using date = std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>; // day / month / year

    class Book // book itself
    {
        friend class TheBook;
        friend class read::Reader;

        QString title_;
        QString author_;
        bool isUsing_;                                                                       // using status
        QVector<std::pair<std::shared_ptr<read::Reader>, std::pair<date, date>>> readers_;   // reader / dates

    public:
        Book(const QString& title, const QString& author) noexcept :
            title_(title), author_(author) { isUsing_ = false; }
        Book(QString&& title, QString&& author)           noexcept :
            title_(title), author_(author) { isUsing_ = false; }
        ~Book() = default;

        void changeTitle (QString&& title)          noexcept { title_  = title; }
        void changeTitle (const QString& title)     noexcept { title_  = title; }
        void changeAuthor(QString&& author)         noexcept { author_ = author; }
        void changeAuthor(const QString& author)    noexcept { author_ = author; }

        void startReading(std::shared_ptr<read::Reader>, date)    noexcept;
        void finishReading(std::shared_ptr<read::Reader>)         noexcept;

        [[nodiscard]] bool isUse()          const noexcept { return isUsing_; }
        [[nodiscard]] QString getTitle()    const noexcept { return title_; }
        [[nodiscard]] QString getAuthor()   const noexcept { return author_; }

        [[nodiscard]] QVector<std::pair<std::shared_ptr<read::Reader>,
        std::pair<date, date>>>::const_reverse_iterator getLastReader()  const noexcept { return readers_.rbegin(); }
    };

    class TheBook // interface
    {
        friend class BookSystem;

        QString title_;
        QString author_;
        QVector<std::shared_ptr<Book>> books_; // books with same params

    public:
        TheBook(QString&& title, QString&& author)           noexcept :
            title_(title), author_(author) {}
        TheBook(const QString& title, const QString& author) noexcept :
            title_(title), author_(author) {}
        [[nodiscard]] bool operator== (const TheBook& theBook) noexcept { return title_ == theBook.title_ && author_ == theBook.author_; }
        [[nodiscard]] bool operator!= (const TheBook& theBook) noexcept { return !(*this == theBook); }
        ~TheBook() = default;

        [[nodiscard]] QString getTitle()                                const noexcept { return title_; }
        [[nodiscard]] QString getAuthor()                               const noexcept { return author_; }
        [[nodiscard]] QVector<std::shared_ptr<Book>>::const_iterator cend()   noexcept { return books_.cend(); }
        [[nodiscard]] QVector<std::shared_ptr<Book>>::iterator getUnused()    noexcept;

        void changeTitle(QString&&)                         noexcept;
        void changeTitle(const QString&)                    noexcept;
        void changeAuthor(QString&&)                        noexcept;
        void changeAuthor(const QString&)                   noexcept;
        void removeBook(const std::size_t ind)              noexcept { books_.erase(books_.begin() + ind); }
        void addBook()                                      noexcept { books_.push_back(std::make_shared<Book>(title_, author_)); }
    };

    class BookSystem
    {
        friend class read::Reader;

        QVector<std::shared_ptr<TheBook>> books_;
        static std::shared_ptr<BookSystem> instance_;

    public:
        BookSystem()                                = default;
        BookSystem(const BookSystem&)               = delete;
        BookSystem(BookSystem&&)                    = delete;
        ~BookSystem()                               = default;
        BookSystem& operator=(const BookSystem&)    = delete;
        BookSystem& operator=(BookSystem&&)         = delete;

        [[nodiscard]] bool addBook(std::shared_ptr<TheBook>)                noexcept;
        [[nodiscard]] bool addBook(QString&&, QString&&)                    noexcept;
        [[nodiscard]] bool addBook(const QString&, const QString&)          noexcept;

        [[nodiscard]] QVector<std::shared_ptr<TheBook>>::iterator find(std::shared_ptr<TheBook>)           noexcept;
        [[nodiscard]] QVector<std::shared_ptr<TheBook>>::iterator find(QString&&, QString&&)               noexcept;
        [[nodiscard]] QVector<std::shared_ptr<TheBook>>::iterator find(const QString&, const QString&)     noexcept;
        [[nodiscard]] QVector<std::shared_ptr<TheBook>>::const_iterator cend()                       const noexcept { return books_.cend(); }

        [[nodiscard]] bool removeBook(std::shared_ptr<TheBook>)                           noexcept;
        [[nodiscard]] bool removeBook(QString&&, QString&&)                               noexcept;
        [[nodiscard]] bool removeBook(const QString&, const QString&)                     noexcept;

        [[nodiscard]] static std::shared_ptr<BookSystem> getInstance()                    noexcept;
        [[nodiscard]] std::shared_ptr<Book> getUnused(QString&&, QString&&)               noexcept;
        [[nodiscard]] std::shared_ptr<Book> getUnused(const QString&, const QString&)     noexcept;
    };
}

#endif // BOOK_H
