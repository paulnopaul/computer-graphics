#include "ellipse.h"

#include <cmath>

using namespace Ellipses;
using namespace std;

Ellipse::Ellipse(double x0, double y0, double a, double b) :
    x0_(x0), y0_(y0), a_(a), b_(b)
{
}

Ellipse::Ellipse(Algo algo, double x0, double y0, double a, double b) :
    Ellipse(x0, y0, a, b)
{
    if (algo == Algo::CANONICAL)
        points_ = Canonical(x0, y0, a, b);
    else if (algo == Algo::PARAMETRIC)
        points_ = Parametrical(x0, y0, a, b);
    else if (algo == Algo::BRESENHAM)
        points_ = Bresenham(x0, y0, a, b);
    else if (algo == Algo::MIDPOINT)
        points_ = MidPoint(x0, y0, a, b);
    else
        points_.reset();
}


double Ellipse::GetX0() const
{
    return x0_;
}

double Ellipse::GetY0() const
{
    return y0_;
}

double Ellipse::GetA() const
{
    return a_;
}

double Ellipse::GetB() const
{
    return b_;
}


bool Ellipse::IsLibrary() const
{
    return !points_.has_value();
}

void Ellipse::PushBack(QPoint point)
{
    this->points_->push_back(point);
}

void Ellipse::EmplaceBack(int x, int y)
{
    this->points_->emplace_back(x, y);
}

vector<QPoint>::iterator Ellipse::begin()
{
    return points_->begin();
}

vector<QPoint>::const_iterator Ellipse::begin() const
{
    return points_->begin();
}

vector<QPoint>::iterator Ellipse::end()
{
    return points_->end();
}

vector<QPoint>::const_iterator Ellipse::end() const
{
    return points_->end();
}

QRectF Ellipse::GetRect() const
{
    QRectF rect;
    rect.setX(x0_ - a_);
    rect.setY(y0_ - b_);
    rect.setWidth(2 * a_);
    rect.setHeight(2 * b_);
    return rect;
}

void QuartMirror(vector<QPoint> &points, int x, int y, int x0, int y0)
{    
    points.emplace_back(x0 + x, y0 + y);
    points.emplace_back(x0 + x, y0 - y);
    points.emplace_back(x0 - x, y0 + y);
    points.emplace_back(x0 - x, y0 - y);
}

void OctMirror(vector<QPoint> &points, int x, int y, int x0, int y0)
{
    QuartMirror(points, x, y, x0, y0);

    points.emplace_back(x0 + y, y0 + x);
    points.emplace_back(x0 + y, y0 - x);
    points.emplace_back(x0 - y, y0 + x);
    points.emplace_back(x0 - y, y0 - x);
}

namespace Ellipses
{

    vector<QPoint> Canonical(double x0, double y0, double a, double b)
    {
        vector<QPoint> points;
        int xn = a;
        for (int x = 0; x < xn; ++x)
        {
            int y = ceil(b * sqrt(a * a - x * x) / a);;
            QuartMirror(points, x, y, x0, y0);
        }

        int yn = b;
        for (int y = 0; y <= yn; ++y)
        {
            int x = ceil(a * sqrt(b * b - y * y) / b);
            QuartMirror(points, x, y, x0, y0);
        }
        return points;
    }

    vector<QPoint> Parametrical(double x0, double y0, double a, double b)
    {
        vector<QPoint> points; 
        double step = 1 / max(a, b);
        for (double t = 0; t < PI / 2 + step; t += step)
        {
            int x = round(a * cos(t)), y = round(b * sin(t));
            QuartMirror(points, x, y, x0, y0);
        }
        return points;
    }

    vector<QPoint> Bresenham(double x0, double y0, double a, double b)
    {
        vector<QPoint> points;

        long x = 0;
        long y = b;
        long bb = b * b;
        long aa = a * a;
        long d = bb - aa * (2 * b + 1);

        while (y >= 0)
        {
            QuartMirror(points, x, y, x0, y0);
            if (d <= 0)
            {
                long d1 = 2 * d + aa * (2 * y - 1);
                x += 1;
                d += bb * (2 * x + 1);
                if (d1 >= 0)
                {
                    y -= 1;
                    d += aa * (1 - 2 * y);
                }
            }
            else
            {
                long d2 = 2 * d + bb * (1 - 2 * x);
                y -= 1;
                d += aa * (1 - 2 * y);
                if (d2 < 0)
                {
                    x += 1;
                    d += bb * (2 * x + 1);
                }
            }
        }
        return points;
    }

    vector<QPoint> MidPoint(double x0, double y0, double a, double b)
    {
        vector<QPoint> points;
        long bb = b * b, aa = a * a;
        long x = 0, y = b;
        long dx = 2 * bb * x;
        long dy = 2 * aa * y;

        double p1 = bb - aa * b + 0.25 * aa;
        while (dx < dy)
        {
            QuartMirror(points, x, y, x0, y0);

            x++;
            dx += 2 * bb;

            if (p1 >= 0)
            {
                y--;
                dy -= 2 * aa;
                p1 -= dy;
            }
            p1 += dx + bb;
        }

        double p2 = bb * (x + 0.5) * (x + 0.5)  + aa * (y - 1) * (y - 1)  - aa * bb;
        while (y >= 0)
        {
            QuartMirror(points, x, y, x0, y0);
            y--;
            dy -= 2 * aa;

            if (p2 <= 0)
            {
                x++;
                dx += 2 * bb;
                p2 += dx;
            }
            p2 -= dy - aa;
        }
        return points;
    }
}
