#ifndef ABSTRACTINFORMATION_H
#define ABSTRACTINFORMATION_H

#include "reader.h"

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

namespace info
{

    class TheBookInformation : public QDialog
    {
        Q_OBJECT

    public:
        TheBookInformation(QString&&, QString&&, std::size_t)           noexcept;
        TheBookInformation(const QString&, const QString&, std::size_t) noexcept;
        ~TheBookInformation() noexcept { delete ok_; }

    private:
        QPushButton* ok_;
        QLabel bookTitle_;
        QLabel bookAuthor_;
        QLabel booksAmount_;
    };

    class ReaderInformation : public QListWidget
    {
        Q_OBJECT

    public:
        ReaderInformation(QString&&, QString&&)             noexcept;
        ReaderInformation(const QString&, const QString&)   noexcept;
        ReaderInformation(std::shared_ptr<read::Reader>)    noexcept;
        ~ReaderInformation() noexcept { delete ok_; }

    private:
        QPushButton* ok_;
        QVector<std::pair<QString, QString>> books_;
    };

}

#endif // ABSTRACTINFORMATION_H
