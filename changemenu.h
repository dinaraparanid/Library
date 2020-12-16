#ifndef ASKMENU_H
#define ASKMENU_H

#include <memory>
#include <functional>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ChangeMenu : public QDialog
{
    Q_OBJECT

public:
    ChangeMenu(QString&&, QString&&, std::shared_ptr<QString>);
    ChangeMenu(const QString&, const QString&, const std::shared_ptr<QString>);
    ~ChangeMenu();
signals:
    void okPressed();

public slots:
    void change();

private:
    std::shared_ptr<QString> changable_;     // something, that we need to change (book or reader)
    QLabel what_;                            // Input first (name, title of book ...)
    QLineEdit input_;
    QPushButton* ok_;
    QPushButton* cancel_;
};

#endif // ASKMENU_H
