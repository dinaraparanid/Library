#include "Reader.h"

read::Reader::Reader() noexcept
{
	std::printf("Input name\n");
	std::string name;
	std::cin >> name;
	name_ = std::move(name);

	std::printf("Input family\n");
	std::string family;
	std::cin >> name;
	family_ = std::move(family);
}

std::shared_ptr<read::Reader> read::Reader::change_name() noexcept
{
	if (sure())
	{
		std::printf("Input new name\n");
		std::string new_name;
		std::cin >> new_name;
		name_ = std::move(new_name);
	}

	return shared_from_this();
}

std::shared_ptr<read::Reader> read::Reader::change_family() noexcept
{
	if (sure())
	{
		std::printf("Input new family\n");
		std::string new_family;
		std::cin >> new_family;
		family_ = std::move(new_family);
	}

	return shared_from_this();
}

void read::Reader::start_reading()
{
	size_t book = 0;

	while (book == 0)
	{
		const size_t size = booksys::BookSystem::get_instance()->print_unused();

		std::printf("Choose book\n");
		std::cin >> book;

		incorrect_input(book == 0 || book > size);
	}

	std::shared_ptr<booksys::Book> search;
	__TRY__(search = booksys::BookSystem::get_instance()->get_unused(book - 1));
	search->start_reading(shared_from_this());
	books_.push_back(search);
}

void read::Reader::print_info() noexcept
{
	std::printf("Name: %s\nFamily: %s\nBooks:\n", name_.c_str(), family_.c_str());

	for (size_t i = 0; i < books_.size(); i++)
		std::printf("%zu. Title: %s Author: %s\n",
			i + 1, books_[i]->get_title().c_str(), books_[i]->get_author().c_str());
}

std::shared_ptr<read::ReaderBase> read::ReaderBase::get_instance() noexcept
{
	if (!instance_)
		instance_ = std::make_shared<ReaderBase>();
	return instance_;
}

void read::ReaderBase::print_readers() noexcept
{
	for (size_t i = 0; i < readers_.size(); i++)
	{
		std::printf("====%zu====\n", i + 1);
		readers_[i].print_info();
		std::putchar('\n');
	}
}

void read::ReaderBase::add_reader() noexcept
{
	if (sure())
	{
		const auto new_reader = Reader();

		if ([readers = &readers_, &new_reader]()
			{
				for (auto it = readers->begin(); it != readers->end(); ++it)
				{
					if (it->name_ == new_reader.name_ && it->family_ == new_reader.family_)
						return it;
				}

				return readers->end();
			}() == readers_.end())
			readers_.push_back(new_reader);

		else
			std::printf("Student with name %s and family %s is already exists\n",
				new_reader.name_.c_str(), new_reader.family_.c_str());
	}
}

void read::ReaderBase::remove_reader() noexcept
{
	if (sure())
	{
		size_t reader = 0;

		while (reader == 0 || reader > readers_.size())
		{
			print_readers();
			std::printf("Choose reader\n");
			std::cin >> reader;

			incorrect_input(reader == 0 || reader > readers_.size());
		}

		readers_.erase(readers_.begin() + (reader - 1));
	}
}

void read::ReaderBase::print_late() noexcept
{
	for (size_t i = 0, ind = 0; i < readers_.size(); i++)
	{
		if (readers_[i].late())
		{
			std::printf("====%zu====", ind++);
			readers_[i].print_late();
		}
	}
}
