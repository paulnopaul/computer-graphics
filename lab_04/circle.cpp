#include "circle.h"

using namespace Circles;

Circle::Circle(Algo algo, double x0, double y0, double r) :
    Ellipse(x0, y0, r, r)
{
    if (algo == Algo::CANONICAL)
        points_ = Canonical(x0, y0, r);
    else if (algo == Algo::PARAMETRIC)
        points_ = Parametrical(x0, y0, r);
    else if (algo == Algo::BRESENHAM)
        points_ = Bresenham(x0, y0, r);
    else if (algo == Algo::MIDPOINT)
        points_ = MidPoint(x0, y0, r);
    else
        points_.reset();
}

double Circle::GetR() const
{
    return GetA();
}

namespace Circles
{
    std::vector<QPoint> Canonical(double x0, double y0, double r)
    {
        std::vector<QPoint> points;
        return {};
    }

    std::vector<QPoint> Parametrical(double x0, double y0, double r)
    {
        std::vector<QPoint> points;
        return {};
    }

    std::vector<QPoint> Bresenham(double x0, double y0, double r)
    {
        std::vector<QPoint> points;
        return {};
    }

    std::vector<QPoint> MidPoint(double x0, double y0, double r)
    {
        std::vector<QPoint> points;
        return {};
    }
}
