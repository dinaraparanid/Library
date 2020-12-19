#include "changemenu.h"
#include "messagedialog.h"
#include <QFont>

chng::Input1::Input1(QString&& title, QString&& what, QString* set) noexcept :
    menu_(new SubMenu(title)),
    what_(QLabel(what, menu_)),
    input_(QLineEdit(menu_)),
    set_(set)
{
    menu_->ok_->setGeometry(320, 100, 75, 25);
    menu_->cancel_->setGeometry(410, 100, 75, 25);

    what_.setFont(QFont("Calibri", 12, 5));
    input_.setFont(QFont("Calibri Light", 15, 3, true));
    input_.setPlaceholderText("Input something");

    what_.setGeometry(10, 50, 200, 30);
    input_.setGeometry(150, 50, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

chng::Input1::Input1(const QString& title, const QString& what, QString* set) noexcept :
    menu_(new SubMenu(title)),
    what_(QLabel(what, menu_)),
    input_(QLineEdit(menu_)),
    set_(set)
{
    menu_->ok_->setGeometry(320, 100, 75, 25);
    menu_->cancel_->setGeometry(410, 100, 75, 25);

    what_.setFont(QFont("Calibri", 12, 5));
    input_.setFont(QFont("Calibri Light", 15, 3, true));
    input_.setPlaceholderText("Input something");

    what_.setGeometry(10, 50, 200, 30);
    input_.setGeometry(150, 50, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

void chng::Input1::setInput()
{
    if (!input_.text().toStdString().empty())
    {
        *set_ = input_.text();
        qDebug("after %s", set_->toStdString().c_str());
        input_.clear();
        emit okPressed();
    }

    else
    {
        input_.clear();
        MessageDialog* empty = new MessageDialog("Nothing inputted");
        empty->exec();
        delete empty;
    }
}

chng::Input2::Input2(QString&& title, QString&& what1, QString&& what2, QString* set1, QString* set2) noexcept :
    menu_(new SubMenu(title)),
    what1_(QLabel(what1, menu_)),
    input1_(QLineEdit(menu_)),
    set1_(set1),
    what2_(QLabel(what2, menu_)),
    input2_(QLineEdit(menu_)),
    set2_(set2)
{
    menu_->ok_->setGeometry(320, 100, 75, 25);
    menu_->cancel_->setGeometry(410, 100, 75, 25);

    what1_.setFont(QFont("Calibri", 12, 5));
    input1_.setFont(QFont("Calibri Light", 15, 3, true));
    input1_.setPlaceholderText("Input something");
    what1_.setGeometry(10, 20, 200, 30);
    input1_.setGeometry(150, 20, 300, 30);

    what2_.setFont(QFont("Calibri", 12, 5));
    input2_.setFont(QFont("Calibri Light", 15, 3, true));
    input2_.setPlaceholderText("Input something");
    what2_.setGeometry(10, 60, 200, 30);
    input2_.setGeometry(150, 60, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

chng::Input2::Input2(const QString& title, const QString& what1, const QString& what2, QString* set1, QString* set2) noexcept :
    menu_(new SubMenu(title)),
    what1_(QLabel(what1, menu_)),
    input1_(QLineEdit(menu_)),
    set1_(set1),
    what2_(QLabel(what2, menu_)),
    input2_(QLineEdit(menu_)),
    set2_(set2)
{
    menu_->ok_->setGeometry(320, 100, 75, 25);
    menu_->cancel_->setGeometry(410, 100, 75, 25);

    what1_.setFont(QFont("Calibri", 12, 5));
    input1_.setFont(QFont("Calibri Light", 15, 3, true));
    input1_.setPlaceholderText("Input something");
    what1_.setGeometry(10, 20, 200, 30);
    input1_.setGeometry(150, 20, 300, 30);

    what2_.setFont(QFont("Calibri", 12, 5));
    input2_.setFont(QFont("Calibri Light", 15, 3, true));
    input2_.setPlaceholderText("Input something");
    what2_.setGeometry(10, 100, 200, 30);
    input2_.setGeometry(150, 100, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

void chng::Input2::setInput()
{

    if (!input1_.text().toStdString().empty() && !input2_.text().toStdString().empty())
    {
        *set1_ = input1_.text();
        *set2_ = input2_.text();
        qDebug("after %s %s", set1_->toStdString().c_str(), set2_->toStdString().c_str());
        input1_.clear();
        input2_.clear();
        emit okPressed();
    }

    else
    {
        input1_.clear();
        input2_.clear();

        MessageDialog* empty = new MessageDialog("Nothing inputted");
        empty->exec();
        delete empty;
    }
}
