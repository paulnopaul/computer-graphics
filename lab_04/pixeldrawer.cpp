#include "pixeldrawer.h"

using namespace std;

PaintObject::PaintObject(const Ellipse &ellipse, const QColor color) :
    ellipse_(ellipse),
    color_(color)
{
}

vector<QPoint>::iterator PaintObject::begin()
{
    return ellipse_.begin();
}

vector<QPoint>::iterator PaintObject::end()
{
    return ellipse_.end();
}

const vector<QPoint>::const_iterator PaintObject::begin() const
{
    return ellipse_.begin();
}

const vector<QPoint>::const_iterator PaintObject::end() const
{
    return ellipse_.end();
}

QColor PaintObject::GetColor() const
{
    return color_;
}

const Ellipse& PaintObject::GetEllipse() const
{
    return ellipse_;
}

PixelDrawer::PixelDrawer(QWidget *parent) : QWidget(parent)
{
}

void PixelDrawer::DrawEvent()
{
    QPainter p(this);
    p.fillRect(this->rect(), Qt::white);
    this->DrawObjects(p);
    this->DrawScale(p, 50);
}

void PixelDrawer::Draw()
{
    this->update();
}



void PixelDrawer::paintEvent(QPaintEvent *event)
{
    DrawEvent();
}

void PixelDrawer::DrawObject(QPainter &painter, const PaintObject &object)
{
    painter.setPen(object.GetColor());
    if (!object.GetEllipse().IsLibrary())
        for (const QPoint &point: object)
            painter.drawPoint(point);
    else
        painter.drawEllipse(object.GetEllipse().GetRect());
}

void PixelDrawer::DrawObjects(QPainter &painter)
{
    for (const PaintObject &object: objects)
        DrawObject(painter, object);
}

void PixelDrawer::DrawScale(QPainter &painter, int step)
{
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 12));
    for (int x = 0; x < this->width(); x += step)
    {
        painter.drawLine(x, 0, x, 10);
        painter.drawText(x + 2, 22, QString(to_string(x).c_str()));
    }
    for (int y = step; y < this->height(); y += step)
    {
        painter.drawLine(0, y, 10, y);
        painter.drawText(12, y - 2, QString(to_string(y).c_str()));
    }
}
void PixelDrawer::Clear()
{
    this->objects.clear();
}

void PixelDrawer::Add(const PaintObject &object)
{
    this->objects.push_back(object);
}

void PixelDrawer::AddEllipse(const Ellipse &ellipse, QColor color)
{
    this->objects.emplace_back(ellipse, color);
}
