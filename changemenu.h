#ifndef ASKMENU_H
#define ASKMENU_H

#include <memory>

#include "submenu.h"

#include <QMenu>
#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace chng {

    class Input1 : public QObject
    {
        Q_OBJECT

    public:
        Input1(QString&&, QString&&, QString*)           noexcept;
        Input1(const QString&, const QString&, QString*) noexcept;
        ~Input1() { delete menu_; }

    public slots:
        void setInput();
        void show()  { menu_->show(); }
        void close() { menu_->close(); }

    signals:
        void okPressed();

    private:
        SubMenu* menu_;
        QLabel what_;
        QLineEdit input_;
        QString* set_;
    };

    class Input2 : public QObject
    {
        Q_OBJECT

    public:
        Input2(QString&&, QString&&, QString&&, QString*, QString*)                   noexcept;
        Input2(const QString&, const QString&, const QString&, QString*, QString*)    noexcept;
        ~Input2() { delete menu_; }

    public slots:
        void setInput();
        void show()  { menu_->show(); }
        void exec()  { menu_->exec(); }
        void close() { menu_->close(); }

    signals:
        void okPressed();

    private:
        SubMenu* menu_;
        QLabel what1_;
        QLineEdit input1_;
        QString* set1_;
        QLabel what2_;
        QLineEdit input2_;
        QString* set2_;
    };
}

#endif // ASKMENU_H
