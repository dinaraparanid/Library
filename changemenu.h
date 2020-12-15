#ifndef ASKMENU_H
#define ASKMENU_H

#include <memory>
#include <functional>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

template<class T> class ChangeMenu : public QDialog
{
    Q_OBJECT

public:
    ChangeMenu(QString&&, QString&&, QString&&,
               std::shared_ptr<T>, std::function<void(T)>);
    ChangeMenu(const QString&, const QString&, const QString&,  // move constructor
               std::shared_ptr<T>, std::function<void(T)>);     // copy constructor
    void change();                                              // change something
    ~ChangeMenu();

public slots:
    void okPressed();

signals:
    void changed();

private:
    std::shared_ptr<T> changable_;              // something, that we need to change (book or reader)
    std::function<void(T)> func_;               // change function
    QLabel* firstWhat_;                         // Input first (name, title of book ...)
    QLabel* secondWhat_;                        // Input second (family, author ...)
    QLineEdit* firstInput_;
    QLineEdit* secondInput_;
    QPushButton* ok_;
    QPushButton* cancel_;
};

#endif // ASKMENU_H
