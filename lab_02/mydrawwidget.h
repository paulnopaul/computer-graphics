#ifndef MYDRAWWIDGET_H
#define MYDRAWWIDGET_H

#include <QWidget>
#include <QPainter>


class MyDrawWidget : public QWidget
{
public:
    MyDrawWidget(QWidget *parent);
    void paintEvent(QPaintEvent *event=nullptr);
private:
};

#endif // MYDRAWWIDGET_H
