#include "mydrawwidget.h"

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QBrush(Qt::white));


    p.rotate(10);
    p.drawLine(10, 10, 100, 100);
}
