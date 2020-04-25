#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent),
    color(Qt::white)
{
}

void ColorWidget::Update(QColor color)
{
    this->color = color;
    this->update();
}

void ColorWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QBrush(color));
}
