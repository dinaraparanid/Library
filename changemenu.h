#ifndef ASKMENU_H
#define ASKMENU_H

#include <debug.h>

#include <memory>

#include "submenu.h"

#include <QMenu>
#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace chng
{

    class AbstractInput : public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractInput (QString&& title) : menu_(new SubMenu(title)) {}
        explicit AbstractInput (const QString& title) : menu_(new SubMenu(title)) {}
        virtual ~AbstractInput() noexcept { delete menu_; }

    public slots:
        virtual void setInput() = 0;
        virtual void show()     = 0;
        virtual void exec()     = 0;
        virtual void close()    = 0;

    protected:
        SubMenu* menu_;
    };

    class Input1 : public AbstractInput
    {
        Q_OBJECT

    public:
        Input1(QString&&, QString&&, QString*)           noexcept;
        Input1(const QString&, const QString&, QString*) noexcept;
        ~Input1() override { delete menu_; }

    public slots:
        void setInput() override;
        void show()     override { menu_->show(); }
        void exec()     override { menu_->exec(); }
        void close()    override { menu_->close(); }

    signals:
        void okPressed();

    private:
        QLabel what_;
        QLineEdit input_;
        QString* set_;
    };

    class Input2 : public AbstractInput
    {
        Q_OBJECT

    public:
        Input2(QString&&, QString&&, QString&&, QString*, QString*)                   noexcept;
        Input2(const QString&, const QString&, const QString&, QString*, QString*)    noexcept;
        ~Input2() override { delete menu_; }

    public slots:
        void setInput() override;
        void show()     override { menu_->show(); }
        void exec()     override { menu_->exec(); }
        void close()    override { menu_->close(); }

    signals:
        void okPressed();

    private:
        QLabel what1_;
        QLineEdit input1_;
        QString* set1_;
        QLabel what2_;
        QLineEdit input2_;
        QString* set2_;
    };

    class Input3 : public AbstractInput
    {
        Q_OBJECT

    public:
        Input3(QString&&, QString&&, QString&&, QString&&, std::uint8_t*, std::uint8_t*, std::uint16_t*)                        noexcept;
        Input3(const QString&, const QString&, const QString&, const QString&, std::uint8_t*, std::uint8_t*, std::uint16_t*)    noexcept;
        ~Input3() override { delete menu_; }

    public slots:
        void setInput() override;
        void show()     override { menu_->show(); }
        void exec()     override { menu_->exec(); }
        void close()    override { menu_->close(); }

    signals:
        void okPressed();

    private:
        QLabel what1_;
        QLineEdit input1_;
        std::uint8_t* set1_;
        QLabel what2_;
        QLineEdit input2_;
        std::uint8_t* set2_;
        QLabel what3_;
        QLineEdit input3_;
        std::uint16_t* set3_;
    };
}

#endif // ASKMENU_H
