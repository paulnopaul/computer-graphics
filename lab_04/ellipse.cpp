#include "ellipse.h"

using namespace Ellipses;

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
    return points_.has_value();
}

void Ellipse::PushBack(QPoint point)
{
    this->points_->push_back(point);
}

void Ellipse::EmplaceBack(int x, int y)
{
    this->points_->emplace_back(x, y);
}

std::vector<QPoint>::iterator Ellipse::begin()
{
    return points_->begin();
}

std::vector<QPoint>::const_iterator Ellipse::begin() const
{
    return points_->begin();
}

std::vector<QPoint>::iterator Ellipse::end()
{
    return points_->end();
}

std::vector<QPoint>::const_iterator Ellipse::end() const
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
}

namespace Ellipses
{
    std::vector<QPoint> Canonical(double x0, double y0, double a, double b)
    {
        std::vector<QPoint> points;
        return {};
    }

    std::vector<QPoint> Parametrical(double x0, double y0, double a, double b)
    {
        std::vector<QPoint> points;
        return {};
    }

    std::vector<QPoint> Bresenham(double x0, double y0, double a, double b)
    {
        std::vector<QPoint> points;
        return {};
    }

    std::vector<QPoint> MidPoint(double x0, double y0, double a, double b)
    {
        std::vector<QPoint> points;
        return {};
    }
}
