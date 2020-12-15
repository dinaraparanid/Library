#include "changemenu.h"
#include <QFont>

template<class T> ChangeMenu<T>::ChangeMenu(QString&& title,
                                            QString&& firstWhat,
                                            QString&& secondWhat,
                                            std::shared_ptr<T> smthng,
                                            std::function<void(T)> func) :
    firstWhat_(new QLabel(firstWhat, this)),
    secondWhat_(new QLabel(secondWhat, this)),
    firstInput_(new QLineEdit(this)),
    secondInput_(new QLineEdit(this)),
    ok_(new QPushButton("OK", this)),
    cancel_(new QPushButton("Cancel", this)),
    changable_(smthng),
    func_(func)
{
    setGeometry(500, 500, 500, 250);
    setFixedSize(size());
    setWindowTitle(title);

    ok_->setGeometry(320, 220, 75, 25);
    cancel_->setGeometry(410, 220, 75, 25);

    const QFont whatFont("Calibri", 18, 5);
    const QFont editFont("Calibri Light", 15, 3, true);

    firstWhat_->setFont(whatFont);
    secondWhat_->setFont(whatFont);
    firstInput_->setFont(editFont);
    secondInput_->setFont(editFont);

    firstWhat_->setGeometry(10, 50, 200, 30);
    firstInput_->setGeometry(130, 50, 200, 30);

    secondWhat_->setGeometry(10, 150, 200, 30);
    secondInput_->setGeometry(130, 150, 200, 30);

    QObject::connect(ok_, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(cancel_, SIGNAL(pressed()), this, SLOT(close()));
}

template<class T> ChangeMenu<T>::ChangeMenu(const QString& title,
                                            const QString& firstWhat,
                                            const QString& secondWhat,
                                            std::shared_ptr<T> smthng,
                                            std::function<void(T)> func) :
    firstWhat_(new QLabel(firstWhat, this)),
    secondWhat_(new QLabel(secondWhat, this)),
    firstInput_(new QLineEdit(this)),
    secondInput_(new QLineEdit(this)),
    ok_(new QPushButton("OK", this)),
    cancel_(new QPushButton("Cancel", this)),
    changable_(smthng),
    func_(func)
{
    setGeometry(500, 500, 500, 250);
    setFixedSize(size());
    setWindowTitle(title);

    ok_->setGeometry(320, 220, 75, 25);
    cancel_->setGeometry(410, 220, 75, 25);

    const QFont whatFont("Calibri", 18, 5);
    const QFont editFont("Calibri Light", 15, 3, true);

    firstWhat_->setFont(whatFont);
    secondWhat_->setFont(whatFont);
    firstInput_->setFont(editFont);
    secondInput_->setFont(editFont);

    firstWhat_->setGeometry(10, 50, 200, 30);
    firstInput_->setGeometry(130, 50, 200, 30);

    secondWhat_->setGeometry(10, 150, 200, 30);
    secondInput_->setGeometry(130, 150, 200, 30);
}

template<class T> ChangeMenu<T>::~ChangeMenu()
{
    delete firstWhat_;
    delete secondWhat_;
    delete firstInput_;
    delete secondInput_;
    delete ok_;
    delete cancel_;
}

template<class T> void ChangeMenu<T>::change()
{
    func_(changable_)();
}
