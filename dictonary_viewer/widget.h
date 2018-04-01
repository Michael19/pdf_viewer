#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "filemapper.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void next();

private:
    Ui::Widget *ui;

    FileMapper m_mapper;
    QList<QString> m_phrazes;
    QList<QString>::const_iterator m_iter;
};

#endif // WIDGET_H
