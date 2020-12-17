#ifndef ASKMENU_H
#define ASKMENU_H

#include <memory>
#include <any>

#include <QMenu>
#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class InterfaceMenu : public QDialog
{
    Q_OBJECT

public:
    QLabel what_;                            // Input first (name, title of book ...)
    QLineEdit input_;
    QPushButton* ok_;
    QPushButton* cancel_;

    InterfaceMenu(QString&&, QString&&)            noexcept;
    InterfaceMenu(const QString&, const QString&)  noexcept;
    ~InterfaceMenu() { delete ok_; delete cancel_; }
};

class ChangeMenu : public QObject
{
    std::shared_ptr<InterfaceMenu> menu_;
    std::shared_ptr<QString> changable_;

public:
    ChangeMenu(QString&&, QString&&)            noexcept;
    ChangeMenu(const QString&, const QString&)  noexcept;
    ~ChangeMenu() = default;

    void setChangable(std::shared_ptr<QString> changable) noexcept { changable_ = changable; }

signals:
    void okPressed();

public slots:
    void change();
};

template<class T> class AddMenu : public QObject
{
    std::shared_ptr<InterfaceMenu> menu_;
    std::shared_ptr<QVector<T>> container_;
    std::pair<QString, QString> params_;

public:
    AddMenu(QString&&, QString&&)           noexcept;
    AddMenu(const QString&, const QString&) noexcept;
    ~AddMenu() = default;

    void setParams(QString&& f, QString&& s)                 noexcept { params_ = std::make_pair(f, s); }
    void setParams(const QString& f, const QString&& s)      noexcept { params_ = std::make_pair(f, s); }
    void setContainer(std::shared_ptr<QVector<T>> container) noexcept { container_ = container; }

signals:
    void okPressed();

public slots:
    void add();
};

template<class T> class RemoveMenu : public QObject
{
    std::shared_ptr<InterfaceMenu> menu_;
    std::shared_ptr<QVector<T>> container_;
    std::pair<QString, QString> params_;

public:
    RemoveMenu(QString&&, QString&&)            noexcept;
    RemoveMenu(const QString&, const QString&)  noexcept;
    ~RemoveMenu() = default;

    void setParams(QString&& f, QString&& s)                 noexcept { params_ = std::make_pair(f, s); }
    void setParams(const QString& f, const QString&& s)      noexcept { params_ = std::make_pair(f, s); }
    void setContainer(std::shared_ptr<QVector<T>> container) noexcept { container_ = container; }

signals:
    void okPressed();

public slots:
    void remove();
};

#endif // ASKMENU_H
