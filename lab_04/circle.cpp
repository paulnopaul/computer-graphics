#include "circle.h"

#include <cmath>

using namespace std;
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
    double CanonicalUpPixel(double x, double r)
    {
        return ceil(sqrt(r * r - x * x));
    }

    vector<QPoint> Canonical(double x0, double y0, double r)
    {
        vector<QPoint> points;
        int xn = ceil(r);
        for (int x = 0; x <= xn; ++x)
        {
            int y = CanonicalUpPixel(x, r);
            OctMirror(points, x, y, x0, y0);
        }
        return points;
    }

    vector<QPoint> Parametrical(double x0, double y0, double r)
    {
        vector<QPoint> points;
        double step = 1 / r;

        for (double t = 0; t < PI / 2 + step; t += step)
        {
            int x = round(r * cos(t));
            int y = round(r * sin(t));
            QuartMirror(points, x, y, x0, y0);
        }

        return points;
    }

    vector<QPoint> Bresenham(double x0, double y0, double r)
    {
        vector<QPoint> points;
        int x = 0, y = r;
        int d = 2 * (1 - r);

        while (y >= 0)
        {
            QuartMirror(points, x, y, x0, y0);

            if (d <= 0)
            {
                int d1 = 2 * d + 2 * y - 1;
                x++;
                if (d1 < 0)
                    d += 2 * x + 1;
                else
                {
                    y--;
                    d += 2 * (x - y + 1);
                }
            }
            else
            {
                int d2 = 2 * (d - x) - 1;
                y--;
                if (d2 > 0)
                    d -= 2 * y + 1;
                else
                {
                    x++;
                    d += 2 * (x - y + 1);
                }
            }
        }

        return points;
    }

    vector<QPoint> MidPoint(double x0, double y0, double r)
    {
        vector<QPoint> points;
        int x = r, y = 0;
        int d = 1 - r;

        while (x >= y)
        {
            OctMirror(points, x, y, x0, y0);

            y++;
            if (d >= 0)
            {
                x--;;
                d -= 2 * (x - 1);
            }
            d += 2 * y + 3;
        }
        return points;
    }
}
