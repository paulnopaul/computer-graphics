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
    int CanonicalUpPixel(int x, double x0, double y0, double a, double b)
    {
        return round(y0 - b  * sqrt(a*a - x * x + 2 * x * x0 - x0 * x0) / a);
    }

    int CanonicalDownPixel(int x, double x0, double y0, double a, double b)
    {
        return round(y0 + b  * sqrt(a*a - x * x + 2 * x * x0 - x0 * x0) / a);
    }

    vector<QPoint> Canonical(double x0, double y0, double a, double b)
    {
        vector<QPoint> points;
        int xn = round(x0 + a);
        for (int x = round(x0 - a); x < xn; ++x)
        {
            int up_y =      CanonicalUpPixel(x, x0, y0, a, b);
            int down_y =    CanonicalDownPixel(x, x0, y0, a, b);
            points.emplace_back(x, up_y);
            points.emplace_back(x, down_y);
        }

        int yn = round(x0 + b);
        for (int y = round(x0 - b); y < yn; ++y)
        {
            int right_x =   CanonicalUpPixel(y, x0, y0, b, a);
            int left_x =    CanonicalDownPixel(y, x0, y0, b, a);
            points.emplace_back(right_x, y);
            points.emplace_back(left_x, y);
        }
        return points;
    }

    vector<QPoint> Parametrical(double x0, double y0, double a, double b)
    {
        vector<QPoint> points; 
        double step = 1 / max(a, b);
        double tn = step + PI;
        for (double t = 0; t < tn; t += step)
        {
            double v1 = a * cos(t), v2 = a * sin(t);

            double x = int(x0 + v1);
            double y = int(y0 + v2);
            points.emplace_back(x, y);

            x = int(x0 - v1);
            y = int(y0 - v2);
            points.emplace_back(x, y);
        }
        return points;
    }

    vector<QPoint> Bresenham(double x0, double y0, double a, double b)
    {
        vector<QPoint> points;
        int x = 0;
        int y = b;
        int bb = b * b;
        int aa = a * a;
        int delta = bb - aa * (2 * b + 1);

        while (y >= 0)
        {
             QuartMirror(points, x, y, x0, y0);
            if (delta <= 0)
            {
                int delta_temp = 2 * delta + aa * (2 * y - 1);
                x += 1;
                delta += bb * (2 * x + 1);
                if (delta_temp >= 0)
                {
                    y -= 1;
                    delta += aa * (1 - 2 * y);
                }
            }
            else
            {
                int delta_temp = 2 * delta + bb * (1 - 2 * x);
                y -= 1;
                delta += aa * (1 - 2 * y);
                if (delta_temp < 0)
                {
                    x += 1;
                    delta += bb * (2 * x + 1);
                }
            }
        }
        return points;
    }

    vector<QPoint> MidPoint(double x0, double y0, double a, double b)
    {
        vector<QPoint> points;
        int bb = b * b, aa = a * a;
        int x = 0, y = b;
        int delta = bb - aa * b + 0.25 * aa;
        int dx = 2 * bb * x;
        int dy = 2 * aa * y;

        while (dx < dy)
        {
            QuartMirror(points, x, y, x0, y0);

            x++;
            dx += 2 * bb;

            if (delta >= 0)
            {
                y--;
                dy -= 2 * aa;
                delta -= dy;
            }
            delta += dx + bb;
        }
        delta = bb * (x + 0.5) * (x + 0.5)  + aa * (y - 1) * (y - 1)  - aa * bb;

        while (y >= 0)
        {
            QuartMirror(points, x, y, x0, y0);
            y--;
            dy -= 2 * aa;

            if (delta <= 0)
            {
                x++;
                dx += 2 * bb;
                delta += dx;
            }
            delta -= dy - aa;
        }
        return points;
    }
}
