
#include "mydrawwidget.h"
#include "mysolution.h"

#include <cstdio>
using namespace std;

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
    p.translate(this->rect().bottomLeft());
    p.scale(1.0, -1.0);
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    QPen redPen(Qt::red);

    p.fillRect(this->rect(), whiteBrush);

    if (this->complete || this->solved)
        this->setScale();
    if (this->complete)
        this->drawArea(p);
    if (this->solved)
        this->drawSolution(p);

    p.end();
}

void MyDrawWidget::setScale()
{
    pair<double, double> left, right, up, down;
    double height, width;

    left = this->leftPoint();
    right = this->rightPoint();
    up = this->upPoint();
    down = this->downPoint();

    height = this->rect().height() - 10;
    width = this->rect().width() - 10;

    this->scale = min(height / fabs(up.second - down.second),
                      width / fabs(left.first - right.first));
    this->move.first = -left.first;
    this->move.second = -down.second;
}

pair<double, double> MyDrawWidget::leftPoint()
{
    pair<double, double> point = this->dots[0];
    for (const pair<double, double> &p : this->dots)
        if (point.first > p.first)
            point = p;
    for (const pair<double, double> &p : this->triangle)
        if (point.first > p.first)
            point = p;
    if (solved && point.first > resPoint.first - resR)
        point = {resPoint.first - resR, resPoint.second};
   return point;
}

pair<double, double> MyDrawWidget::rightPoint()
{
    pair<double, double> point = this->dots[0];
    for (const pair<double, double> &p : this->dots)
        if (point.first < p.first)
            point = p;
    for (const pair<double, double> &p : this->triangle)
        if (point.first < p.first)
            point = p;
    if (point.first < (resPoint.first + resR))
        point = {resPoint.first + resR, resPoint.second};
    // cout << "LDFKJSKLFJLSD " << resPoint.first + resR << " "<< point.first << endl;
    return point;
}

pair<double, double> MyDrawWidget::downPoint()
{
    pair<double, double> point = this->dots[0];
    for (const pair<double, double> &p : this->dots)
        if (point.second > p.second)
            point = p;
    for (const pair<double, double> &p : this->triangle)
        if (point.second > p.second)
            point = p;
    if (solved && point.second > resPoint.second - resR)
        point = {resPoint.first, resPoint.second - resR};
    return point;
}

pair<double, double> MyDrawWidget::upPoint()
{
    pair<double, double> point = this->dots[0];
    for (const pair<double, double> &p : this->dots)
        if (point.second < p.second)
            point = p;
    for (const pair<double, double> &p : this->triangle)
        if (point.second < p.second)
            point = p;
    if (solved && point.second < resPoint.second + resR)
        point = {resPoint.first, resPoint.second + resR};
    return point;
}

void MyDrawWidget::drawArea(QPainter &p)
{
    QBrush redBrush(Qt::red);
    QBrush transBrush(Qt::transparent);
    QPen bluePen(Qt::blue);
    QPen blackPen(Qt::black);
    p.setPen(blackPen);

    p.setBrush(redBrush);
    for (const pair<double, double> &d : this->dots)
    {
        this->drawCenterCircle(p, (d.first + this->move.first) * scale,
                      (d.second + this->move.second) * scale, 5);
        // cout << (d.first - this->move.first) * scale << " " << (d.second - this->move.second) * scale << endl;
    }

    p.setPen(bluePen);
    p.setBrush(transBrush);
    QPolygonF tri({QPointF((this->triangle[0].first + this->move.first) * scale,
                           (this->triangle[0].second + this->move.second) * scale),
                   QPointF((this->triangle[1].first + this->move.first) * scale,
                           (this->triangle[1].second + this->move.second) * scale),
                   QPointF((this->triangle[2].first + this->move.first) * scale,
                           (this->triangle[2].second + this->move.second) * scale)});

    // this->drawCenterCircle(p, (tCenter.first + this->move.first) * scale,
     //              (tCenter.second + this->move.second) * scale, 3);

    // cout << this->triangle[0].first << " " << this->triangle[0].second << " " <<
    //        this->triangle[1].first << " " << this->triangle[1].second << " " <<
    //        this->triangle[2].first << " " <<  this->triangle[2].second << endl;
    // cout << endl;

    p.drawPolygon(tri);
}

void MyDrawWidget::addSolution(double x0, double y0, double r, double _tx, double _ty)
{
    this->resPoint.first = x0;
    this->resPoint.second = y0;
    this->resR = r;
    this->tx = _tx;
    this->ty = _ty;
}

void MyDrawWidget::drawCenterCircle(QPainter &p, double x0, double y0, double r)
{
    QRectF elRect(x0 - r, y0 - r, r * 2, r * 2);
    p.drawEllipse(elRect);
}

void MyDrawWidget::drawSolution(QPainter &p)
{
    QPen redPen(Qt::green, 2);
    p.setPen(redPen);
    drawCenterCircle(p, (resPoint.first + move.first) * scale,
                     (resPoint.second + move.second) * scale,
                     resR * scale);
    drawCenterCircle(p, (resPoint.first + move.first) * scale,
                     (resPoint.second + move.second) * scale,
                     1);


    QPen greenPen(Qt::red, 2);
    p.setPen(greenPen);
    pair<double, double> tCenter = MySolution::triangleCenter(triangle[0],
            triangle[1], triangle[2]);
    QPolygonF tri({QPointF((this->resPoint.first + this->move.first) * scale,
                           (this->resPoint.second + this->move.second) * scale),
                   QPointF((tCenter.first + this->move.first) * scale,
                           (tCenter.second + this->move.second) * scale),
                   QPointF((this->tx + this->move.first) * scale,
                           (this->ty + this->move.second) * scale)});
    p.drawPolygon(tri);
    cout << tx << " " << ty << endl;
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
