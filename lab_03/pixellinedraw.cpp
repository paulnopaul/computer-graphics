#include "pixellinedraw.h"
#include <iostream>


PixelLineDraw::PixelLineDraw(QWidget *parent) : QWidget(parent),
    type(AlgoType::DEFAULT),
    startPoint(0, 0),
    endPoint(400, 100),
    mainColor(Qt::black)
{
}

void PixelLineDraw::clear()
{
    lines.clear();
    this->update();
}

void rotPoint(double rc, double rs,
              QPoint &endPoint, QPoint startPoint)
{
    double x = endPoint.x() - startPoint.x();
    double y = endPoint.y() - startPoint.y();

    double x1 = x * rc - y * rs;
    double y1 = x * rs + y * rc;
    x1 += startPoint.x();
    y1 += startPoint.y();

    endPoint.setX(x1);
    endPoint.setY(y1);
}

void PixelLineDraw::drawLine(QPoint start, QPoint end,
                             AlgoType _type, QColor color)
{
    lines.emplace_back(start, end, _type, color);
    this->update();
}

void PixelLineDraw::drawDifferentLines(double rotateAngle,
                                       AlgoType _type,
                                       QColor color)
{
    int len = 200;
    const double pi = 3.1415926535;
    int count = ceil(pi * 2 / rotateAngle);

    startPoint.setX(300);
    startPoint.setY(300);

    endPoint = startPoint;
    endPoint.setX(startPoint.x() + len);

    double rc = cos(rotateAngle);
    double rs = sin(rotateAngle);

    for (int i = 0; i < count; ++i)
    {
        this->lines.emplace_back(startPoint, endPoint, _type, color);
        rotPoint(rc, rs, endPoint, startPoint);
    }
    this->update();
}

void PixelLineDraw::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(), QBrush(Qt::white));
    this->drawScale(p);
    for (MyLine &line: lines)
        this->drawOneLine(p, line);
}

void PixelLineDraw::drawOneLine(QPainter &p, MyLine &line)
{
    this->startPoint = line.start;
    this->endPoint = line.end;
    this->mainColor = line.color;
    this->type = line.type;
    p.setPen(this->mainColor);

    if (type == AlgoType::DDA)
        this->drawDDA(p);
    else if (type == AlgoType::WU)
        this->drawWu(p);
    else if (type == AlgoType::FLOAT_BRESENHAM)
        this->drawFloatBresenham(p);
    else if (type == AlgoType::INT_BRESENHAM)
        this->drawIntBresenham(p);
    else if (type == AlgoType::SMOOTH_BRESENHAM)
        this->drawSmoothBresenham(p);
    else if (type == AlgoType::LIBRARY)
        this->drawLibrary(p);
}

void PixelLineDraw::drawDDA(QPainter &p)
{
        if ((abs(startPoint.x() - endPoint.x()) == 0) &&
            (fabs(startPoint.y() - endPoint.y()) == 0))
        {
            p.drawPoint(startPoint);
            return;
        }
        double dx = endPoint.x() - startPoint.x();
        double dy = endPoint.y() - startPoint.y();
        double l = std::max(fabs(dx), fabs(dy));

        dx = dx / l;
        dy = dy / l;

        double x = startPoint.x();
        double y = startPoint.y();

        for (int i = 0; i <= l; i++)
        {
            p.drawPoint(round(x), round(y));
            x = x + dx;
            y = y + dy;
        }
}

void PixelLineDraw::drawLibrary(QPainter &p)
{
    p.drawLine(startPoint, endPoint);
}

void PixelLineDraw::drawPoint(QPainter &p, double x, double y, double intensivity)
{
    QColor thisColor(mainColor.red(), mainColor.green(), mainColor.blue(), int(255 * intensivity));
    p.setPen(QPen(thisColor));
    p.drawPoint(x, y);
}

void PixelLineDraw::drawPointInt(QPainter &p, int x, int y, int intensivity)
{
    QColor thisColor(mainColor.red(), mainColor.green(), mainColor.blue(), intensivity);
    p.setPen(QPen(thisColor));
    p.drawPoint(x, y);
}


void PixelLineDraw::drawWu(QPainter &p)
{
    double x0 = startPoint.x(), x1 = endPoint.x();
    double y0 = startPoint.y(), y1 = endPoint.y();
    auto ipart = [](float x) -> int {return int(std::floor(x));};
    auto round = [](float x) -> float {return std::round(x);};
    auto fpart = [](float x) -> float {return x - std::floor(x);};
    auto rfpart = [=](float x) -> float {return 1 - fpart(x);};

    const bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep)
    {
        std::swap(x0,y0);
        std::swap(x1,y1);
    }
    if (x0 > x1)
    {
        std::swap(x0,x1);
        std::swap(y0,y1);
    }

    const float dx = x1 - x0;
    const float dy = y1 - y0;
    const float gradient = (dx == 0) ? 1 : dy / dx;

    int xpx11;
    float intery;
    {
        const float xend = round(x0);
        const float yend = y0 + gradient * (xend - x0);
        const float xgap = rfpart(x0 + 0.5);
        xpx11 = int(xend);
        const int ypx11 = ipart(yend);
        if (steep)
        {
            drawPoint(p, ypx11, xpx11, rfpart(yend) * xgap);
            drawPoint(p, ypx11 + 1, xpx11, fpart(yend) * xgap);
        } else
        {
            drawPoint(p, xpx11, ypx11, rfpart(yend) * xgap);
            drawPoint(p, xpx11, ypx11 + 1, fpart(yend) * xgap);
        }
        intery = yend + gradient;
    }

    int xpx12;
    {
        const float xend = round(x1);
        const float yend = y1 + gradient * (xend - x1);
        const float xgap = rfpart(x1 + 0.5);
        xpx12 = int(xend);
        const int ypx12 = ipart(yend);
        if (steep)
        {
            drawPoint(p,ypx12, xpx12, rfpart(yend) * xgap);
            drawPoint(p,ypx12 + 1, xpx12, fpart(yend) * xgap);
        } else
        {
            drawPoint(p, xpx12, ypx12, rfpart(yend) * xgap);
            drawPoint(p, xpx12, ypx12 + 1, fpart(yend) * xgap);
        }
    }

    if (steep)
        for (int x = xpx11 + 1; x < xpx12; x++)
        {
            drawPoint(p, ipart(intery), x, rfpart(intery));
            drawPoint(p, ipart(intery) + 1, x, fpart(intery));
            intery += gradient;
        }
    else
        for (int x = xpx11 + 1; x < xpx12; x++)
        {
            drawPoint(p, x, ipart(intery), rfpart(intery));
            drawPoint(p, x, ipart(intery) + 1, fpart(intery));
            intery += gradient;
        }
}

void PixelLineDraw::drawIntBresenham(QPainter &p)
{
    int dx = endPoint.x() - startPoint.x();
    int dy = endPoint.y() - startPoint.y();
    if (abs(dx) == 0 && abs(dy) == 0)
    {
        p.drawPoint(startPoint);
        return;
    }

    int sx = sgn(dx);
    int sy = sgn(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool change = false;
    if (dy >= dx)
    {
        swap(dx, dy);
        change = true;
    }
    int e = 2 * dy - dx;
    int x = startPoint.x();
    int y = startPoint.y();

    for (int i = 0; i <= dx; i++)
    {
        p.drawPoint(x, y);
        if (e >= 0)
        {
            if (change)
                x = x + sx;
            else
                y = y + sy;
            e = e - 2 * dx;
        }
        if (change)
            y = y + sy;
        else
            x = x + sx;
        e = e + 2 * dy;
    }
}

void PixelLineDraw::drawFloatBresenham(QPainter &p)
{
    int dx = endPoint.x() - startPoint.x();
    int dy = endPoint.y() - startPoint.y();
    if (abs(dx) == 0 && abs(dy) == 0)
    {
        p.drawPoint(startPoint);
        return;
    }

    int sx = sgn(dx);
    int sy = sgn(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool change = false;
    if (dy >= dx)
    {
        swap(dx, dy);
        change = true;
    }
    double m = (double)dy / dx;
    double e = m - 0.5;
    int x = startPoint.x();
    int y = startPoint.y();

    for (int i = 0; i <= dx; i++)
    {
        p.drawPoint(x, y);
        if (e >= 0)
        {
            if (change)
                x = x + sx;
            else
                y = y + sy;
            e -= 1;
        }
        if (change)
            y = y + sy;
        else
            x = x + sx;
        e += m;
    }
}

void PixelLineDraw::drawSmoothBresenham(QPainter &p)
{
    int dx = endPoint.x() - startPoint.x();
    int dy = endPoint.y() - startPoint.y();
    if (abs(dx) == 0 && abs(dy) == 0)
    {
        p.drawPoint(startPoint);
        return;
    }

    int sx = sgn(dx);
    int sy = sgn(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool change = false;
    if (dy > dx)
    {
        swap(dx, dy);
        change = true;
    }
    double m = double(dy) / dx;
    int i_max = 256;
    double e = i_max / 2;
    int x = startPoint.x();
    int y = startPoint.y();
    m = m * i_max;
    double w = i_max - m;

    p.drawPoint(x, y);
    for (int i = 0; i < dx; i++)
    {
        if (e <= w)
        {
            if (change)
                y = y + sy;
            else
                x = x + sx;
            e += m;
        }
        else
        {
            y = y + sy;
            x = x + sx;
            e -= w;
        }
        this->drawPoint(p, x, y, 1 - (e / i_max));
    }
}



void PixelLineDraw::drawScale(QPainter &p)
{
    int step = 50;
    int x = p.window().width() - p.window().width() % step;
    int y = p.window().height() - p.window().height() % step;
    p.setPen(Qt::black);
    for (int i = 0; i < y; i += step)
    {
        p.drawLine(0, i + 1, 10, i + 1);
        p.drawText(10, i + 12, QString(to_string(i).c_str()));
    }

    for (int i = step; i < x; i += step)
    {
        p.drawLine(i, 0, i, 10);
        p.drawText(i + 2, 20, QString(to_string(i).c_str()));
    }
}


