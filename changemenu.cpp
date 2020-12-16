#include "changemenu.h"
#include <QFont>

ChangeMenu::ChangeMenu(QString&& title,
                       QString&& what,
                       std::shared_ptr<QString> smthng) :
    changable_(smthng),
    what_(QLabel(what, this)),
    input_(QLineEdit(this)),
    ok_(new QPushButton("OK", this)),
    cancel_(new QPushButton("Cancel", this))
{
    setGeometry(500, 500, 500, 150);
    setFixedSize(size());
    setWindowTitle(title);

    ok_->setGeometry(320, 100, 75, 25);
    cancel_->setGeometry(410, 100, 75, 25);

    what_.setFont(QFont("Calibri", 18, 5));
    input_.setFont(QFont("Calibri Light", 15, 3, true));

    what_.setGeometry(10, 50, 200, 30);
    input_.setGeometry(150, 50, 300, 30);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(change()));
    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(cancel_, SIGNAL(pressed()), this, SLOT(close()));
}

ChangeMenu::ChangeMenu(const QString& title,
                       const QString& what,
                       std::shared_ptr<QString> smthng) :
    changable_(smthng),
    what_(QLabel(what, this)),
    input_(QLineEdit(this)),
    ok_(new QPushButton("OK", this)),
    cancel_(new QPushButton("Cancel", this))
{
    setGeometry(500, 500, 500, 150);
    setFixedSize(size());
    setWindowTitle(title);

    ok_->setGeometry(320, 100, 75, 25);
    cancel_->setGeometry(410, 100, 75, 25);

    what_.setFont(QFont("Calibri", 18, 5));
    input_.setFont(QFont("Calibri Light", 15, 3, true));

    what_.setGeometry(10, 50, 200, 30);
    input_.setGeometry(150, 50, 300, 30);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(change()));
    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(cancel_, SIGNAL(pressed()), this, SLOT(close()));
}

ChangeMenu::~ChangeMenu()
{
    delete ok_;
    delete cancel_;
}

void ChangeMenu::change()
{
    *changable_ = input_.text();
    qDebug(changable_->toStdString().c_str());
    emit okPressed();
}
