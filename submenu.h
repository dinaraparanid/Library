#ifndef SUBMENU_H
#define SUBMENU_H

#include <debug.h>

#ifdef RELEASE
#undef DEBUG
#endif

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class SubMenu : public QDialog
{
    Q_OBJECT

public:
    QLabel title_;
    QPushButton* ok_;
    QPushButton* cancel_;

    SubMenu(QString&&)       noexcept;
    SubMenu(const QString&)  noexcept;
    ~SubMenu() { delete ok_; delete cancel_; }
};

#endif // SUBMENU_H
