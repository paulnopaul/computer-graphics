#ifndef CIRCLE_H
#define CIRCLE_H

#include <ellipse.h>

class Circle : public Ellipse
{
public:
    double GetR() const;
    Circle(Algo algo, double x0, double y0, double r);
};

namespace Circles
{
    std::vector<QPoint> Canonical(double x0, double y0, double r);

    std::vector<QPoint> Parametrical(double x0, double y0, double r);

    std::vector<QPoint> Bresenham(double x0, double y0, double r);

    std::vector<QPoint> MidPoint(double x0, double y0, double r);
}


#endif // CIRCLE_H
