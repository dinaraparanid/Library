#include "changemenu.h"
#include <QFont>

InterfaceMenu::InterfaceMenu(QString&& title, QString&& what) noexcept :
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

InterfaceMenu::InterfaceMenu(const QString& title, const QString& what) noexcept :
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

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(cancel_, SIGNAL(pressed()), this, SLOT(close()));
}

ChangeMenu::ChangeMenu(QString&& title, QString&& what) noexcept :
    menu_(std::make_shared<InterfaceMenu>(title, what)) {
    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(change()));
}

ChangeMenu::ChangeMenu(const QString& title, const QString& what) noexcept :
    menu_(std::make_shared<InterfaceMenu>(title, what)) {
    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(change()));
}

void ChangeMenu::change()
{
    *changable_ = menu_->input_.text();
    qDebug("%s", changable_->toStdString().c_str());
    emit okPressed();
}

template<class T>AddMenu<T>::AddMenu(QString&& title, QString&& what) noexcept :
    menu_(std::make_shared<InterfaceMenu>(title, what)) {
    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(add()));
}

template<class T>AddMenu<T>::AddMenu(const QString& title, const QString& what) noexcept :
    menu_(std::make_shared<InterfaceMenu>(title, what)) {
    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(add()));
}

template<class T> void AddMenu<T>::add()
{
    const T pattern(params_.first, params_.second);

    for (auto it = container_->begin(); it != container_->end(); ++it)
    {
        if (*it == pattern)
        {
            emit okPressed();
            return;
        }
    }

    container_->push_back(pattern);
    qDebug("add");
    emit okPressed();
}

template<class T>RemoveMenu<T>::RemoveMenu(QString&& title, QString&& what) noexcept :
    menu_(std::make_shared<InterfaceMenu>(title, what)) {
    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(remove()));
}

template<class T>RemoveMenu<T>::RemoveMenu(const QString& title, const QString& what) noexcept :
    menu_(std::make_shared<InterfaceMenu>(title, what)) {
    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(remove()));
}

template<class T> void RemoveMenu<T>::remove()
{
    const T pattern(params_.first, params_.second);

    for (auto it = container_->begin(); it != container_->end(); ++it)
    {
        if (*it == pattern)
        {
            container_->erase(it);
            qDebug("remove");
            emit okPressed();
        }
    }

    emit okPressed();
}
