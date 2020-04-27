#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QPointF>
#include <QRectF>

#include <vector>
#include <optional>
#include <functional>

#define PI 3.14159265359

class Ellipse
{
public:
    enum class Algo
    {
        CANONICAL,
        PARAMETRIC,
        BRESENHAM,
        MIDPOINT,
        LIBRARY,
    };

    Ellipse(double x0, double y0, double a, double b);

    Ellipse(Algo algo, double x0, double y0, double a, double b);

    double GetX0() const;

    double GetY0() const;

    double GetA() const;

    double GetB() const;

    bool IsLibrary() const;

    void PushBack(QPoint point);

    void EmplaceBack(int x, int y);

    std::vector<QPoint>::iterator begin();

    std::vector<QPoint>::const_iterator begin() const;

    std::vector<QPoint>::iterator end();

    std::vector<QPoint>::const_iterator end() const;

    QRectF GetRect() const;

protected:
    std::optional<std::vector<QPoint>> points_;
    double x0_, y0_, a_, b_;
};

void QuartMirror(std::vector<QPoint> &points, int x, int y, int x0, int y0);

void OctMirror(std::vector<QPoint> &points, int x, int y, int x0, int y0);


namespace Ellipses
{
    std::vector<QPoint> Canonical(double x0, double y0, double a, double b);

    std::vector<QPoint> Parametrical(double x0, double y0, double a, double b);

    std::vector<QPoint> Bresenham(double x0, double y0, double a, double b);

    std::vector<QPoint> MidPoint(double x0, double y0, double a, double b);
}


#endif // ELLIPSE_H
