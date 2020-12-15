#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QDialog>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QMenu* readerMenu_;
    QMenu* bookMenu_;
    QMenu* helpMenu_;
    QMenuBar* mainMenu_;

};
#endif // MAINWINDOW_H
