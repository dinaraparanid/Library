#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <debug.h>

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QPushButton>

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QString&&)      noexcept;
    explicit MessageDialog(const QString&) noexcept;
    ~MessageDialog() noexcept { delete ok_; }

private:
    QLabel mesg_;
    QPushButton* ok_;
};

#endif // MESSAGEDIALOG_H
