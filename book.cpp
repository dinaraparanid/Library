#include "book.h"
#include "reader.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <chrono>
#include <ctime>

std::shared_ptr<booksys::BookSystem> booksys::BookSystem::instance_;

std::shared_ptr<booksys::Book>& booksys::BookSystem::get_unused(const size_t ind)
{
    std::size_t index = 1;

    for (auto& the_book : books_)
    {
        for (auto& book : the_book->get_books())
        {
            if (!book->is_use())
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

void booksys::BookSystem::add_book() noexcept
{
    if (sure())
    {
        const auto new_book = TheBook();
        const auto ptr = std::make_shared<TheBook>(new_book);
        const auto new_name = std::make_pair(new_book.get_title(), new_book.get_author());

        if ([books = &books_, &new_name]()
            {
                for (auto it = books->begin(); it != books->end(); ++it)
                {
                    const auto name = std::make_pair(it->get()->get_title(), it->get()->get_author());

                        if (new_name == name)
                            return it;
                }

                return books->end();
            }() == books_.end())
            books_.push_back(ptr);

        else
            std::printf("Book with title %s and author %s is already exists\n",
                new_book.get_title().c_str(), new_book.get_author().c_str());
    }
}

void booksys::BookSystem::print_books() noexcept
{
    std::size_t i = 1;

    for (const auto& book : books_)
    {
        std::printf("====%zu====\n", i++);
        book->print_book();
    }
}

std::size_t booksys::BookSystem::print_unused() noexcept
{
    std::size_t ind = 1;

    for (const auto& the_book : books_)
    {
        for (const auto& book : the_book->get_books())
        {
            if (!book->is_use())
            {
                std::printf("====%zu====", ind++);
                the_book->print_book();
                break;
            }
        }
    }

    return ind;
}

std::shared_ptr<booksys::BookSystem> booksys::BookSystem::get_instance() noexcept
{
    if (!instance_)
        instance_ = std::make_shared<BookSystem>();
    return instance_;
}

void booksys::BookSystem::remove_book() noexcept
{
    if (sure())
    {
        size_t book = 0;

        while (book == 0 || book > books_.size())
        {
            print_books();
            std::printf("Choose book\n");
            std::cin >> book;

            incorrect_input(book == 0 || book > books_.size());
        }

        books_.erase(books_.begin() + (book - 1));
    }
}

void booksys::Book::start_reading(const std::shared_ptr<read::Reader>& reader) noexcept
{
    const auto start = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const std::tm now = *std::localtime(&start);

    std::printf("Input finish date 'd/m/y'\n");

    std::uint8_t d = 0, m = 0, y = 0;

    do std::scanf("%c/%c/%c", &d, &m, &y);
    while (sure());

    readers_.emplace_back(reader,
                          std::make_pair(std::make_tuple(now.tm_mday, now.tm_mon, now.tm_year),
                                         std::make_tuple(d, m, y)), 0);

    is_using_ = true;
}

void booksys::Book::finish_reading() noexcept
{
    const auto finish = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const std::tm now = *std::localtime(&finish);

    std::uint8_t stat = 0;

    while (stat < min_status || stat > max_status)
    {
        std::printf("Input status\n");
        std::cin >> stat;

        incorrect_input(stat < min_status || stat > max_status);
    }

    is_using_ = false;
    std::get<1>(readers_.back()).second = std::make_tuple(now.tm_mday, now.tm_mon, now.tm_year);
    std::get<2>(readers_.back()) = stat;
}

void booksys::Book::print_book_info() noexcept
{
    for (std::size_t i = 0; i < readers_.size(); i++)
    {
        std::printf("%zu Name: %s %s, Start reading: %c/%c/%hu, Finish reading: ",
                    i + 1,
                    std::get<0>(readers_[i])->get_family().c_str(),
                    std::get<0>(readers_[i])->get_name().c_str(),
                    std::get<0>(std::get<1>(readers_[i]).first),
                    std::get<1>(std::get<1>(readers_[i]).first),
                    std::get<2>(std::get<1>(readers_[i]).first));

        if (is_using_)
            std::printf("Still in use\n");

        else
            std::printf("%c/%c/%hu\n",
                        std::get<0>(std::get<1>(readers_[i]).second),
                        std::get<1>(std::get<1>(readers_[i]).second),
                        std::get<2>(std::get<1>(readers_[i]).second));
    }
}

void booksys::Book::partial_print_book_info() noexcept
{
    const auto& readers = readers_;

    std::size_t i = [&readers]()
    {
        if (readers.size() < 5)
            return size_t(0);
        return readers.size() - 5;
    }();

    for (std::size_t q = 1; i < readers_.size(); i++, q++)
    {
        std::printf("%zu Name: %s %s, Start reading: %c/%c/%hu, Finish reading: ",
                    q + 1,
                    std::get<0>(readers_[i])->get_family().c_str(),
                    std::get<0>(readers_[i])->get_name().c_str(),
                    std::get<0>(std::get<1>(readers_[i]).first),
                    std::get<1>(std::get<1>(readers_[i]).first),
                    std::get<2>(std::get<1>(readers_[i]).first));

        if (is_using_)
            std::printf("Still in use\n");
        else
            std::printf("%c/%c/%hu\n",
                        std::get<0>(std::get<1>(readers_[i]).second),
                        std::get<1>(std::get<1>(readers_[i]).second),
                        std::get<2>(std::get<1>(readers_[i]).second));
    }
}

booksys::TheBook::TheBook() noexcept
{
    std::string title;
    std::printf("Input title\n");
    std::cin >> title;
    title_ = std::move(title);

    std::string author;
    std::printf("Input author\n");
    std::cin >> author;
    author_ = std::move(author);

    std::uint8_t genre = 0;

    while (genre == 0 || genre > book_genre.size() + 1)
    {
        std::printf("Choose genres of book:\n");
        print_all_genres();
        std::printf("17.Exit\n");

        std::cin >> genre;

        incorrect_input(genre == 0 || genre > book_genre.size() + 1);

        if (genre == book_genre.size() + 1 && genre_.empty())
            std::printf("You haven't chosen any genre\n");

        else if (genre == book_genre.size() + 1)
            break;

        else
            genre_.insert(book_genre[genre - 1]);
    }

    std::uint16_t pages = 0;

    while (pages == 0)
    {
        std::printf("Input number of pages\n");
        std::cin >> pages;

        incorrect_input(pages == 0);
    }

    pages_ = pages;
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::add_book() noexcept
{
    if (sure())
        books_.push_back(std::make_shared<Book>(Book(title_, author_)));
    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::print_books() noexcept
{
    for (std::size_t i = 0; i < books_.size(); i++)
    {
        std::printf("====%zu====\n", i + 1);
        books_[i]->print_book_info();
        std::putchar('\n');
    }

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::partial_print_books() noexcept
{
    for (std::size_t i = 0; i < books_.size(); i++)
    {
        std::printf("====%zu====\n", i + 1);
        books_[i]->partial_print_book_info();
        std::putchar('\n');
    }

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::change_title() noexcept
{
    if (sure())
    {
        std::printf("Input new title\n");
        std::string title;
        std::cin >> title;
        title_ = std::move(title);

        for (auto& book : books_)
            book->change_title(title_);
    }

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::change_author() noexcept
{
    if (sure())
    {
        std::printf("Input new author\n");
        std::string author;
        std::cin >> author;
        author_ = std::move(author);

        for (auto& book : books_)
            book.get()->change_author(author_);
    }

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::print_genres() noexcept
{
    std::printf("Genres:\n");

    std::size_t i = 1;

    for (const auto& genre : genre_)
        std::printf("%zu. %s\n", i++, genre.c_str());

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::remove_genre() noexcept
{
    if (sure())
    {
        std::uint8_t genre = 0;

        while (genre < 1 || genre > genre_.size())
        {
            std::size_t i = 1;

            for (const auto& gen : genre_)
                std::printf("%zu. %s\n", i++, gen.c_str());

            std::printf("Input genre\n");
            std::cin >> genre;

            incorrect_input(genre < 1 || genre > genre_.size());
        }

        auto erase = genre_.begin();
        std::advance(erase, genre - 1);
        genre_.erase(erase);
    }

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::add_genre() noexcept
{
    if (sure())
    {
        std::uint8_t genre = 0;

        while (genre == 0 || genre > book_genre.size() + 1)
        {
            std::printf("Choose genres of book:\n");
            print_all_genres();
            std::cin >> genre;

            incorrect_input(genre == 0 || genre > book_genre.size() + 1);

            if (genre > 0 && genre <= book_genre.size())
                genre_.insert(book_genre[genre - 1]);

            else if (genre == book_genre.size() + 1)
                break;
        }
    }

    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::print_book() noexcept
{
    std::printf("Title: %s\nAuthor: %s\n", title_.c_str(), author_.c_str());
    print_genres();
    return shared_from_this();
}

std::shared_ptr<booksys::TheBook> booksys::TheBook::remove_book() noexcept
{
    if (sure())
    {
        std::size_t book = 0;

        while (book == 0 || book > books_.size())
        {
            partial_print_books();

            std::printf("Choose book\n");
            std::cin >> book;

            incorrect_input(book == 0 || book > books_.size());
        }

        books_.erase(books_.begin() + (book - 1));
    }

    return shared_from_this();
}
