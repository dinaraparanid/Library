#include <debug.h>

#ifdef RELEASE
#undef DEBUG
#endif

#include "messagedialog.h"

MessageDialog::MessageDialog(QString&& mesg) noexcept :
    mesg_(mesg, this),
    ok_(new QPushButton("OK", this))
{
    setGeometry(500, 500, 500, 150);
    setFixedSize(size());
    setWindowTitle(mesg_.text());

    ok_->setGeometry(320, 100, 75, 25);
    mesg_.setFont(QFont("Times", 18, 5));
    mesg_.setGeometry(150, 50, 300, 30);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}

MessageDialog::MessageDialog(const QString& mesg) noexcept :
    mesg_(mesg, this),
    ok_(new QPushButton("OK", this))
{
    setGeometry(500, 500, 500, 150);
    setFixedSize(size());
    setWindowTitle(mesg_.text());

    ok_->setGeometry(320, 100, 75, 25);
    mesg_.setFont(QFont("Calibri", 18, 5));
    mesg_.setGeometry(100, 50, 300, 30);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
}
