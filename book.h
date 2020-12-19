#ifndef BOOK_H
#define BOOK_H

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
         bool isUsing_;                                                                      // using status
        QVector<std::pair<std::shared_ptr<read::Reader>, std::pair<date, date>>> readers_;   // reader / dates

    public:
        Book(const QString& title, const QString& author) noexcept :
            title_(title), author_(author) { isUsing_ = false; }
        Book(QString&& title, QString&& author)           noexcept :
            title_(title), author_(author) { isUsing_ = false; }
        ~Book() = default;

        void changeTitle (QString&& title)       noexcept { title_  = title; }
        void changeTitle (const QString& title)  noexcept { title_  = title; }
        void changeAuthor(QString&& author)      noexcept { author_ = author; }
        void changeAuthor(const QString& author) noexcept { author_ = author; }

        void startReading(const std::shared_ptr<read::Reader>&, date) noexcept;
        void finishReading()										  noexcept;

        [[nodiscard]] bool isUse()		  const noexcept { return isUsing_; }
        [[nodiscard]] QString getTitle()  const noexcept { return title_; }
        [[nodiscard]] QString getAuthor() const noexcept { return author_; }
    };

    class TheBook // interface
    {
        friend class BookSystem;

        QString title_;
        QString author_;
        QVector<Book> books_; // books with same params

    public:
        TheBook(QString&& title, QString&& author)           noexcept :
            title_(title), author_(author) {}
        TheBook(const QString& title, const QString& author) noexcept :
            title_(title), author_(author) {}
        bool operator== (const TheBook& theBook) { return title_ == theBook.title_ && author_ == theBook.author_; }
        bool operator!= (const TheBook& theBook) { return !(*this == theBook); }
        ~TheBook() = default;

        [[nodiscard]] QString getTitle()        const noexcept { return title_; }
        [[nodiscard]] QString getAuthor()       const noexcept { return author_; }

        void changeTitle(QString&& title)        noexcept { title_  = title; }
        void changeTitle(const QString& title)   noexcept { title_  = title; }
        void changeAuthor(QString&& author)      noexcept { author_ = author; }
        void changeAuthor(const QString& author) noexcept { author_ = author; }
        void removeBook(const std::size_t ind)   noexcept { books_.erase(books_.begin() + ind); }
        void addBook()                           noexcept { books_.push_back(Book(title_, author_)); }
    };

    class BookSystem
    {
        friend class read::Reader;

        QVector<TheBook> books_;
        static std::shared_ptr<BookSystem> instance_;

        Book& getUnused(std::size_t ind);

    public:
        BookSystem() = default;
        BookSystem(const BookSystem&) = delete;
        BookSystem(BookSystem&&) = delete;
        ~BookSystem() = default;
        BookSystem& operator=(const BookSystem&) = delete;
        BookSystem& operator=(BookSystem&&) = delete;

        bool addBook(TheBook&&)                                            noexcept;
        bool addBook(const TheBook&)                                       noexcept;
        bool addBook(QString&&, QString&&)                                 noexcept;
        bool addBook(const QString&, const QString&)                       noexcept;

        QVector<TheBook>::iterator find(TheBook&&)                         noexcept;
        QVector<TheBook>::iterator find(const TheBook&)                    noexcept;
        QVector<TheBook>::iterator find(QString&&, QString&&)              noexcept;
        QVector<TheBook>::iterator find(const QString&, const QString&)    noexcept;

        bool removeBook(TheBook&&)                                         noexcept;
        bool removeBook(const TheBook&)                                    noexcept;
        bool removeBook(QString&&, QString&&)                              noexcept;
        bool removeBook(const QString&, const QString&)                    noexcept;

        static std::shared_ptr<BookSystem> getInstance() noexcept;
    };
}

#endif // BOOK_H
