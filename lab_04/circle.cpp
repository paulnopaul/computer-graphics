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
    double CanonicalUpPixel(double x, double x0, double y0, double r)
    {
        return round(y0 + sqrt(r * r - x * x + 2 * x * x0 - x0 * x0));
    }

    double CanonicalDownPixel(double x, double x0, double y0, double r)
    {
        return round(y0 - sqrt(r * r - x * x + 2 * x * x0 - x0 * x0));
    }

    vector<QPoint> Canonical(double x0, double y0, double r)
    {
        vector<QPoint> points;
        int xn = round(x0 + r);
        for (int x = round(x0 - r); x <= xn; ++x)
        {
            int up_y =      CanonicalUpPixel(x, x0, y0, r);
            int down_y =    CanonicalDownPixel(x, x0, y0, r);
            points.emplace_back(x, CanonicalUpPixel(x, x0, y0, r));
            points.emplace_back(x, CanonicalDownPixel(x, x0, y0, r));
        }

        int yn = round(y0 + r);
        for (int y = round(y0 - r); y <= yn; ++y)
        {
            int right_x =   CanonicalUpPixel(y, x0, y0, r);
            int left_x =    CanonicalDownPixel(y, x0, y0,r);
            points.emplace_back(right_x, y);
            points.emplace_back(left_x, y);
        }
        return points;
    }

    vector<QPoint> Parametrical(double x0, double y0, double r)
    {
        vector<QPoint> points;
        double step = 1 / r;

        for (double t = 0; t <= 2 * PI; t += step)
        {
            int x = round(x0 + r * cos(t));
            int y = round(y0 + r * sin(t));
            points.emplace_back(x, y);
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
            if (d > 0)
            {
                x--;;
                d -= 2 * (x - 1);
            }
            d += 2 * y + 3;
        }
        return points;
    }
}
