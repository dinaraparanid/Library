#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

class SubWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SubWindow(QWidget *parent = nullptr) : QWidget(parent) {}
    ~SubWindow() = default;
};

#endif // SUBWINDOW_H
