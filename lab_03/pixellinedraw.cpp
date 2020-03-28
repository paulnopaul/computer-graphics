#include "pixellinedraw.h"

PixelLineDraw::PixelLineDraw(QWidget *parent) : QWidget(parent),
    type(AlgoType::DDA),
    startPoint(0, 0),
    endPoint(300, 50)
{

}

void PixelLineDraw::drawLine(QPointF start, QPointF end, AlgoType _type)
{
    startPoint = start;
    endPoint = end;
    type = _type;
    this->update();
}

void PixelLineDraw::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QBrush(Qt::white));
    if (type == AlgoType::DDA)
        this->drawDDA(p);
    else if (type == AlgoType::BRESENHAM)
        this->drawBresenham(p);
}

void PixelLineDraw::drawDDA(QPainter &p)
{
//    double growth = (endPoint.y() - startPoint.y()) / (endPoint.x() - startPoint.x());
//    for (double x = startPoint.x(), y = startPoint.y(); x < endPoint.x(); ++x, y += growth)
//        p.drawPoint(QPointF(x, y));
    double length = std::max(abs(endPoint.x() - startPoint.x()),
                        abs(endPoint.y() - startPoint.y()));
    double dx = (endPoint.x() - startPoint.x()) / length;
    double dy = (endPoint.y() - startPoint.y()) / length;
    double x = startPoint.x() + 0.5 * sgn(dx);
    double y = startPoint.y() + 0.5 * sgn(dx);

    for (int i = 0; i < length; ++i)
    {
        p.drawPoint(int(x), int(y));
        x += dx;
        y += dy;
    }
}

void PixelLineDraw::drawBresenham(QPainter &p)
{
    double x = startPoint.x();
    double y = startPoint.y();
    double dx = abs(endPoint.x() - startPoint.x());
    double dy = abs(endPoint.y() - startPoint.y());
    double s1 = sgn(endPoint.x() - startPoint.x());
    double s2 = sgn(endPoint.y() - startPoint.y());
    bool changed = false;
    if (dx > dy)
    {
        std::swap(dx, dy);
        changed = true;
    }
    double e = 2 * dy - dx;
    for (double i = 0; i < dx; ++i)
    {
        p.drawPoint(x, y);
        while (e >= 0)
        {
            if (changed)
                x += s1;
            else
                y += s2;
            e -= 2 * dx;
        }
        if (changed)
            y += s2;
        else
            x += s1;
        e += 2 * dy;
    }
}
