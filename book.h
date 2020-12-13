#ifndef BOOK_H
#define BOOK_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>
#include <unordered_set>

#define __TRY__(FUNCTION)		\
try { FUNCTION; }			\
catch (const std::logic_error& e)	\
{					\
    std::fputs(e.what(), stderr);	\
    std::terminate();		\
}

namespace
{
    void incorrect_input(const bool x) noexcept { if (x) std::printf("Incorrect input. Try again\n"); }

    bool sure() noexcept
    {
        std::printf("Are you sure you want to do this? If yes then print 'YES'\n");
        std::string yes;
        std::cin >> yes;
        return yes == "YES";
    }
}

namespace read { class Reader; }

namespace booksys
{
    constexpr std::uint8_t min_status = 1;
    constexpr std::uint8_t max_status = 10;

    /*16 standart types of books*/
    inline std::vector<std::string> book_genre
    {
        "Business",
        "Detectives",
        "Thrillers",
        "Scientific",
        "Hobbies and leisure",
        "Drama",
        "Computer",
        "Children",
        "Love",
        "Poetry",
        "Epic_and_prose",
        "Religion",
        "Fantasy",
        "Tech",
        "Humor",
        "Health"
    };

    inline void add_genre()
    {
        if (sure())
        {
            std::printf("Input new genre\n");
            std::string genre;
            std::cin >> genre;

            if (std::find(book_genre.begin(), book_genre.end(), genre) != book_genre.end())
                std::printf("Genre with name %s is already exists\n", genre.c_str());

            else
                book_genre.push_back(genre);
        }
    }

    inline void print_all_genres()
    {
        if (sure())
            for (std::size_t i = 0; i < book_genre.size(); i++)
                std::printf("%zu. %s\n", i + 1, book_genre[i].c_str());
    }

    class Book // book itself
    {
        friend class TheBook;
        friend class read::Reader;

        using date = std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>;	                              // day / month / year
        std::vector<std::tuple<std::shared_ptr<read::Reader>, std::pair<date, date>, std::uint8_t>> readers_; // reader, dates and status
        bool is_using_{ false };									      // using status
        std::string title_;
        std::string author_;

        void change_title (const std::string& title)  noexcept { title_ = title; }
        void change_author(const std::string& author) noexcept { author_ = author; }

    public:
        Book(std::string title, std::string author) noexcept :
            title_(std::move(title)), author_(std::move(author)) {}
        ~Book() = default;

        void start_reading(const std::shared_ptr<read::Reader>& reader) noexcept;
        void finish_reading()											noexcept;

        [[nodiscard]] bool is_use()			   const noexcept { return is_using_; }
        [[nodiscard]] std::string get_title()  const noexcept { return title_; }
        [[nodiscard]] std::string get_author() const noexcept { return author_; }

        /*prints all readers*/
        void print_book_info()		   noexcept;

        /*prints 5 last readers*/
        void partial_print_book_info() noexcept;
    };

    class TheBook : // interface
            std::enable_shared_from_this<TheBook>
    {
        friend class BookSystem;
        friend void remove_genre();

        std::string title_;
        std::string author_;
        std::unordered_set<std::string> genre_;
        std::uint16_t pages_;
        std::vector<std::shared_ptr<Book>> books_; // books with same params

        std::shared_ptr<Book>& get_book(const size_t ind) noexcept { return books_[ind]; }
        std::vector<std::shared_ptr<Book>>& get_books()   noexcept { return books_; }

    public:
        TheBook() noexcept;
        ~TheBook() = default;

        std::shared_ptr<TheBook> add_book()    noexcept;
        std::shared_ptr<TheBook> remove_book() noexcept;

        /*prints all readers*/
        std::shared_ptr<TheBook> print_books() noexcept;

        /*prints 5 last readers*/
        std::shared_ptr<TheBook> partial_print_books() noexcept;

        std::string get_title()  const noexcept { return title_; }
        std::string get_author() const noexcept { return author_; }

        std::shared_ptr<TheBook> change_title()  noexcept;
        std::shared_ptr<TheBook> change_author() noexcept;
        std::shared_ptr<TheBook> print_genres()  noexcept;
        std::shared_ptr<TheBook> remove_genre()  noexcept;
        std::shared_ptr<TheBook> add_genre()     noexcept;
        std::shared_ptr<TheBook> print_book()    noexcept;
    };

    class BookSystem
    {
        friend class read::Reader;
        friend void remove_genre();

        std::vector<std::shared_ptr<TheBook>> books_;
        static std::shared_ptr<BookSystem> instance_;

        std::shared_ptr<Book>& get_unused(size_t ind);

    public:
        BookSystem() = default;
        BookSystem(const BookSystem&) = delete;
        BookSystem(BookSystem&&) = delete;
        ~BookSystem() = default;
        BookSystem& operator=(const BookSystem&) = delete;
        BookSystem& operator=(BookSystem&&) = delete;

        void add_book()									  noexcept;
        void print_books()								  noexcept;
        void remove_book()								  noexcept;
        std::size_t print_unused()						  noexcept;
        static std::shared_ptr<BookSystem> get_instance() noexcept;
    };

    inline void remove_genre()
    {
        if (sure())
        {
            std::size_t i = 0;

            while (i == 0 || i > book_genre.size())
            {
                print_all_genres();
                std::printf("Choose genre\n");
                std::cin >> i;

                incorrect_input(i == 0 || i > book_genre.size());
            }

            i--;

            for (auto& book : BookSystem::get_instance()->books_)
            {
                const auto it = book->genre_.find(book_genre[i]);

                if (it != book->genre_.end())
                    book->genre_.erase(it);
            }

            book_genre.erase(book_genre.begin() + i);
        }
    }
}

#endif // BOOK_H
