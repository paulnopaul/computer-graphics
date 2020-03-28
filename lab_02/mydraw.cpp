#include "mydraw.h"

MyDraw::MyDraw(QWidget *parent) : QWidget(parent)
{
}

void MyDraw::move(double dx, double dy)
{
    fp.move(dx, dy);
}

void MyDraw::scale(double x0, double y0, double dx, double dy)
{
    fp.scale(x0, y0, dx, dy);
}

void MyDraw::rotate(double x0, double y0, double r)
{
    fp.rotate(x0, y0, r);
}

void MyDraw::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QBrush(Qt::white));

    stringstream ss;
    ss << setprecision(3);
    ss << "Центр: " << fp.center().x() << ", " << fp.center().y();
    string s;
    getline(ss, s);
    QString str(s.c_str());
    p.drawText(QPointF(5, 25), str);
    QTransform to_center;
    to_center.translate(this->width() / 2, this->height() / 2);
    p.setTransform(to_center);

    for (const QVector<QPointF> &points: fp.elements)
        if (points.size() > 2)
            p.drawPolygon(points);
        else if (points.size() == 2)
            p.drawLine(points[0].x(), points[0].y(),
                                            points[1].x(), points[1].y());

}

void MyDraw::draw()
{
    this->update();
}

void MyDraw::prev()
{
    fp.prev();
}
