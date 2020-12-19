#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr)      noexcept;
    ~MainWindow();

/*public slots:
    void addBook(QString&&, QString&&)                  noexcept;
    void addBook(const QString&, const QString&)        noexcept;
    void removeBook(QString&&, QString&&)               noexcept;
    void removeBook(const QString&, const QString&)     noexcept;
    void findBook(QString&&, QString&&)                 noexcept;
    void findBook(const QString&, const QString&)       noexcept;

    void addReader(QString&&, QString&&)                noexcept;
    void addReader(const QString&, const QString&)      noexcept;
    void removeReader(QString&&, QString&&)             noexcept;
    void removeReader(const QString&, const QString&)   noexcept;
    void findReader(QString&&, QString&&)               noexcept;
    void findReader(const QString&, const QString&)     noexcept;

    void getHelp()                                      noexcept;
    void giveBookToReader()                             noexcept;
    void getBookFromReader()                            noexcept;

signals:
    void pressedAddBook();
    void pressedRemoveBook();
    void pressedFindBook();

    void pressedAddReader();
    void pressedRemoveReader();
    void pressedFindReader();

    void pressedHelp();*/

private:
    QMenu* readerMenu_;
    QMenu* bookMenu_;
    QMenu* helpMenu_;
    QMenu* giveaway_;
    QMenuBar* mainMenu_;

};
#endif // MAINWINDOW_H
