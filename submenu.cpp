#include "submenu.h"

SubMenu::SubMenu(QString&& title) noexcept :
    title_(title),
    ok_(new QPushButton("OK", this)),
    cancel_(new QPushButton("Cancel", this))
{
    setGeometry(500, 500, 500, 150);
    setFixedSize(size());
    setWindowTitle(title);

    ok_->setGeometry(320, 100, 75, 25);
    cancel_->setGeometry(410, 100, 75, 25);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(cancel_, SIGNAL(pressed()), this, SLOT(close()));
}

SubMenu::SubMenu(const QString& title) noexcept :
    title_(title),
    ok_(new QPushButton("OK", this)),
    cancel_(new QPushButton("Cancel", this))
{
    setGeometry(500, 500, 500, 150);
    setFixedSize(size());
    setWindowTitle(title);

    ok_->setGeometry(320, 100, 75, 25);
    cancel_->setGeometry(410, 100, 75, 25);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(cancel_, SIGNAL(pressed()), this, SLOT(close()));
}
