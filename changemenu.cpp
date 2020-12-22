#include <debug.h>

#include "changemenu.h"
#include "messagedialog.h"

#include <QFont>

#include <chrono>
#include <ctime>

chng::Input1::Input1(QString&& title, QString&& what, QString* set) noexcept :
    AbstractInput(title),
    what_(QLabel(what, menu_)),
    input_(QLineEdit(menu_)),
    set_(set)
{
    menu_->ok_->setGeometry(320, 170, 75, 25);
    menu_->cancel_->setGeometry(410, 170, 75, 25);

    what_.setFont(QFont("Calibri", 12, 5));
    input_.setFont(QFont("Calibri Light", 15, 3, true));
    input_.setPlaceholderText("Input something");

    what_.setGeometry(10, 80, 200, 30);
    input_.setGeometry(150, 80, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

chng::Input1::Input1(const QString& title, const QString& what, QString* set) noexcept :
    AbstractInput(title),
    what_(QLabel(what, menu_)),
    input_(QLineEdit(menu_)),
    set_(set)
{
    menu_->ok_->setGeometry(320, 170, 75, 25);
    menu_->cancel_->setGeometry(410, 170, 75, 25);

    what_.setFont(QFont("Calibri", 12, 5));
    input_.setFont(QFont("Calibri Light", 15, 3, true));
    input_.setPlaceholderText("Input something");

    what_.setGeometry(10, 80, 200, 30);
    input_.setGeometry(150, 80, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

void chng::Input1::setInput()
{
    if (!input_.text().toStdString().empty())
    {
        *set_ = input_.text();

        #ifdef DEBUG
        qDebug("after %s", set_->toStdString().c_str());
        #endif

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
    AbstractInput(title),
    what1_(QLabel(what1, menu_)),
    input1_(QLineEdit(menu_)),
    set1_(set1),
    what2_(QLabel(what2, menu_)),
    input2_(QLineEdit(menu_)),
    set2_(set2)
{
    menu_->ok_->setGeometry(320, 170, 75, 25);
    menu_->cancel_->setGeometry(410, 170, 75, 25);

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

chng::Input2::Input2(const QString& title, const QString& what1, const QString& what2, QString* set1, QString* set2) noexcept :
    AbstractInput(title),
    what1_(QLabel(what1, menu_)),
    input1_(QLineEdit(menu_)),
    set1_(set1),
    what2_(QLabel(what2, menu_)),
    input2_(QLineEdit(menu_)),
    set2_(set2)
{
    menu_->ok_->setGeometry(320, 170, 75, 25);
    menu_->cancel_->setGeometry(410, 170, 75, 25);

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

        #ifdef DEBUG
        qDebug("after %s %s", set1_->toStdString().c_str(), set2_->toStdString().c_str());
        #endif

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

chng::Input3::Input3(QString&& title, QString&& what1, QString&& what2, QString&& what3, std::uint8_t* set1, std::uint8_t* set2, std::uint16_t* set3) noexcept :
    AbstractInput(title),
    what1_(QLabel(what1, menu_)),
    input1_(QLineEdit(menu_)),
    set1_(set1),
    what2_(QLabel(what2, menu_)),
    input2_(QLineEdit(menu_)),
    set2_(set2),
    what3_(QLabel(what3, menu_)),
    input3_(QLineEdit(menu_)),
    set3_(set3)
{
    menu_->ok_->setGeometry(320, 170, 75, 25);
    menu_->cancel_->setGeometry(410, 170, 75, 25);

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

    what3_.setFont(QFont("Calibri", 12, 5));
    input3_.setFont(QFont("Calibri Light", 15, 3, true));
    input3_.setPlaceholderText("Input something");
    what3_.setGeometry(10, 100, 200, 30);
    input3_.setGeometry(150, 100, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

chng::Input3::Input3(const QString& title, const QString& what1, const QString& what2, const QString& what3, std::uint8_t* set1, std::uint8_t* set2, std::uint16_t* set3) noexcept :
    AbstractInput(title),
    what1_(QLabel(what1, menu_)),
    input1_(QLineEdit(menu_)),
    set1_(set1),
    what2_(QLabel(what2, menu_)),
    input2_(QLineEdit(menu_)),
    set2_(set2),
    what3_(QLabel(what3, menu_)),
    input3_(QLineEdit(menu_)),
    set3_(set3)
{
    menu_->ok_->setGeometry(320, 170, 75, 25);
    menu_->cancel_->setGeometry(410, 170, 75, 25);

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

    what3_.setFont(QFont("Calibri", 12, 5));
    input3_.setFont(QFont("Calibri Light", 15, 3, true));
    input3_.setPlaceholderText("Input something");
    what3_.setGeometry(10, 100, 200, 30);
    input3_.setGeometry(150, 100, 300, 30);

    QObject::connect(menu_->ok_, SIGNAL(pressed()), this, SLOT(setInput()));
    QObject::connect(menu_->ok_, SIGNAL(pressed()), menu_, SLOT(close()));
    QObject::connect(menu_->cancel_, SIGNAL(pressed()), menu_, SLOT(close()));
}

void chng::Input3::setInput()
{
    if (!input1_.text().toStdString().empty() && !input2_.text().toStdString().empty() && !input3_.text().toStdString().empty())
    {
        const auto start            = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const auto now              = *std::localtime(&start);

        const std::uint8_t day      = now.tm_mday;
        const std::uint8_t month    = now.tm_mon + 1;
        const std::uint16_t year     = now.tm_year + 1900;

        const std::uint8_t iday     = input1_.text().toUShort();
        const std::uint8_t imonth   = input2_.text().toUShort();
        const std::uint16_t iyear    = input3_.text().toUShort();

        #ifdef DEBUG
        qDebug("Day %hu Month %hu Year %hu", day, month, year);
        qDebug("IDay %hu IMonth %hu IYear %hu", iday, imonth, iyear);
        #endif

        constexpr std::array<std::uint8_t, 12> days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (iyear < year)
        {
            MessageDialog* errDate = new MessageDialog("Incorrect year");
            errDate->exec();
            delete errDate;
        }

        else if (iyear == year)
        {
            if (imonth < month)
            {
                MessageDialog* errDate = new MessageDialog("Incorrect month");
                errDate->exec();
                delete errDate;
            }

            else if (imonth == month)
            {
                if (iday <= day)
                {
                    MessageDialog* errDate = new MessageDialog("Incorrect day");
                    errDate->exec();
                    delete errDate;
                }

                else // iday > day
                {
                    CHECK_DAY:

                    if (imonth != 1)
                    {
                        if (iday <= days[imonth])
                            goto OK;

                        else // iday > days[imonth]
                        {
                            MessageDialog* errDate = new MessageDialog("Incorrect day");
                            errDate->exec();
                            delete errDate;
                        }
                    }

                    else // imonth == 1 (febrary)
                    {
                        if (iyear % 400 == 0 || (iyear % 100 != 0 && iyear % 4 == 0))
                        {
                            if (iday <= 29)
                                goto OK;

                            else // iday > 29
                            {
                                MessageDialog* errDate = new MessageDialog("Incorrect day");
                                errDate->exec();
                                delete errDate;
                            }
                        }
                    }
                }
            }

            else // imonh > month
            {
                CHECK_MONTH:

                if (imonth > 12)
                {
                    MessageDialog* errDate = new MessageDialog("Incorrect month");
                    errDate->exec();
                    delete errDate;
                }

                else
                    goto CHECK_DAY;
            }
        }

        else // iyear > year
        {
            goto CHECK_MONTH;

            OK:

            MessageDialog* succes = new MessageDialog("Finish date setted");
            succes->exec();
            delete succes;

            *set1_ = iday;
            *set2_ = imonth;
            *set3_ = iyear;

            #ifdef DEBUG
            qDebug("after %hu %hu %hu", *set1_, *set2_, *set3_);
            #endif

            emit okPressed();
        }
    }

    else // nothing inputted
    {
        MessageDialog* empty = new MessageDialog("Nothing inputted");
        empty->exec();
        delete empty;
    }

    input1_.clear();
    input2_.clear();
    input3_.clear();
}
