#include "mydrawwidget.h"

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent), triangle(3)
{
    complete = 0;
    solved = 0;
    scale = 1;
}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    event = nullptr;
    QPainter p(this);
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    QPen redPen(Qt::red);


    p.fillRect(this->rect(), whiteBrush);
    if (this->complete)
        this->drawArea(p);
    if (this->solved)
        this->drawSolution(p);
}

void MyDrawWidget::drawArea(QPainter &p)
{
    return;
}

void MyDrawWidget::drawSolution(QPainter &p)
{
    return;
}

void MyDrawWidget::updateTriangle(double x1, double y1,
                                  double x2, double y2,
                                  double x3, double y3)
{
    this->triangle[0] = {x1, y1};
    this->triangle[1] = {x2, y2};
    this->triangle[2] = {x3, y3};
}

void MyDrawWidget::addPoint(double x, double y)
{
    this->dots.push_back({x, y});
}

void MyDrawWidget::deletePoint(int n)
{
    this->dots.erase(this->dots.begin() + n);
}

void MyDrawWidget::isComplete(bool x)
{
    this->complete = x;
}

void MyDrawWidget::isSolved(bool x)
{
    this->solved = x;
}
