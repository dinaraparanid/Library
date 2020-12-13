#ifndef READER_H
#define READER_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Book.h"

namespace read
{
	class Reader : std::enable_shared_from_this<Reader> // just 1 man
	{
		friend class ReaderBase;
		
		std::string name_;
		std::string family_;
		std::vector<std::shared_ptr<booksys::Book>> books_; // books he've read

		void print_late() noexcept
		{
			std::printf("Name: %s\nFamily: %s\nBook: %s %s\n", name_.c_str(), family_.c_str(),
				books_.back()->get_title().c_str(), books_.back()->get_author().c_str());
		}

	public:
		
		Reader() noexcept;
		~Reader() = default;

		bool late() noexcept { return *std::get<0>(books_.back()->readers_.back()) == *this && books_.back()->is_use(); }
		bool operator==(const Reader& reader) const noexcept { return name_ == reader.name_ && family_ == reader.family_; }
		void finish_reading() noexcept { books_.back()->finish_reading(); }
		
		std::string get_name()   const noexcept { return name_; }
		std::string get_family() const noexcept { return family_; }

		void start_reading();
		std::shared_ptr<Reader> change_name()   noexcept;
		std::shared_ptr<Reader> change_family() noexcept;
		void print_info()						noexcept;
	};

	class ReaderBase
	{
		std::vector<Reader> readers_;
		static std::shared_ptr<ReaderBase> instance_;
		
	public:
		ReaderBase() = default;
		ReaderBase(const ReaderBase&) = delete;
		ReaderBase(ReaderBase&&) = delete;
		ReaderBase& operator= (const ReaderBase&) = delete;
		ReaderBase& operator= (ReaderBase&&) = delete;
		~ReaderBase() = default;

		std::shared_ptr<ReaderBase> get_instance() noexcept;
		void print_readers()					   noexcept;
		void add_reader()						   noexcept;
		void remove_reader()					   noexcept;
		void print_late()						   noexcept;
	};
}

#endif // READER_H
