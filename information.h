#ifndef ABSTRACTINFORMATION_H
#define ABSTRACTINFORMATION_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class TheBookInformation : public QDialog
{
    Q_OBJECT

public:
    TheBookInformation(QString&&, QString&&, QString&&, std::size_t)                noexcept;
    TheBookInformation(const QString&, const QString&, const QString&, std::size_t) noexcept;
    ~TheBookInformation() noexcept { delete ok_; }

private:
    QLabel title_;
    QPushButton* ok_;

    QLabel bookTitle_;
    QLabel bookAuthor_;
    QLabel booksAmount_;
};

#endif // ABSTRACTINFORMATION_H
