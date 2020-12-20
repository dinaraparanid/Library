#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <book.h>

#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr)                                                          noexcept;
    ~MainWindow();

    void addBook(QString&&, QString&&)                                                                      noexcept;
    void addBook(const QString&, const QString&)                                                            noexcept;
    void removeBook(QString&&, QString&&)                                                                   noexcept;
    void removeBook(const QString&, const QString&)                                                         noexcept;
    void findBook(QString&&, QString&&)                                                                     noexcept;
    void findBook(const QString&, const QString&)                                                           noexcept;
    void changeTitle(QString&&, QString&&, QString&&)                                                       noexcept;
    void changeTitle(const QString&, const QString&, const QString&)                                        noexcept;
    void changeAuthor(QString&&, QString&&, QString&&)                                                      noexcept;
    void changeAuthor(const QString&, const QString&, const QString&)                                       noexcept;

    void addSimpleBook(QString&&, QString&&, std::size_t)                                                                noexcept;
    void addSimpleBook(const QString&, const QString&, std::size_t)                                                      noexcept;
    void removeSimpleBook(QString&&, QString&&, std::size_t)                                                noexcept;
    void removeSimpleBook(const QString&, const QString&, std::size_t)                                      noexcept;

    void addReader(QString&&, QString&&)                                                                    noexcept;
    void addReader(const QString&, const QString&)                                                          noexcept;
    void removeReader(QString&&, QString&&)                                                                 noexcept;
    void removeReader(const QString&, const QString&)                                                       noexcept;
    void findReader(QString&&, QString&&)                                                                   noexcept;
    void findReader(const QString&, const QString&)                                                         noexcept;
    void changeName(QString&&, QString&&, QString&&)                                                        noexcept;
    void changeName(const QString&, const QString&, const QString&)                                         noexcept;
    void changeFamily(QString&&, QString&&, QString&&)                                                      noexcept;
    void changeFamily(const QString&, const QString&, const QString&)                                       noexcept;

    void getHelp()                                                                                          noexcept;
    void giveBookToReader(QString&&, QString&&, QString&&, QString&&, booksys::date)                        noexcept;
    void giveBookToReader(const QString&, const QString&, const QString&, const QString&, booksys::date)    noexcept;
    void getBookFromReader(QString&&, QString&&, QString&&, QString&&)                                      noexcept;
    void getBookFromReader(const QString&, const QString&, const QString&, const QString&)                  noexcept;

signals:
    void pressedAddBook();
    void pressedRemoveBook();
    void pressedFindBook();

    void pressedAddReader();
    void pressedRemoveReader();
    void pressedFindReader();

    void pressedHelp();

    void pressedGiveBook();
    void pressedGetBook();

private:
    QMenu* readerMenu_;
    QMenu* bookMenu_;
    QMenu* helpMenu_;
    QMenu* giveaway_;
    QMenuBar* mainMenu_;

};
#endif // MAINWINDOW_H
