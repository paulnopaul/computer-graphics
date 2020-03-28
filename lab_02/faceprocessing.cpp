#include "faceprocessing.h"


double ellipseDownPoint(double x, double a, double b, double x0, double y0)
{
    return y0 + (b * sqrt(a * a - x * x + 2 * x * x0 - x0 * x0)) / a;
}

double ellipseUpPoint(double x, double a, double b, double x0, double y0)
{
    return y0 - (b * sqrt(a * a - x * x + 2 * x * x0 - x0 * x0)) / a;
}

QVector<QPointF> generateEllipse(double a, double b, double x0, double y0, int point_count)
{
    QVector<QPointF> points;
    int upPointCount = point_count / 2;
    int downPointCount = ceil(double(point_count / 2));
    double xStart = x0 - a;
    double xEnd = x0 + a;
    double xUpStep = (xEnd - xStart) / upPointCount;
    double xDownStep = (xEnd - xStart) / downPointCount;

    for(double x = xStart; fabs(xEnd - x) > 1e-8; x += xUpStep)
        points.push_back({x, ellipseDownPoint(x, a, b, x0, y0)});

    for(double x = xEnd; fabs(x - xStart) > 1e-8; x -= xDownStep)
        points.push_back({x, ellipseUpPoint(x, a, b, x0, y0)});

    return points;
}

QVector<QPointF> generateTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
{
    return {{x0, y0}, {x1, y1}, {x2, y2}};
}

QVector<QPointF> generateLine(double x0, double y0, double x1, double y1)
{
    return {{x0, y0}, {x1, y1}};
}

void movePoint(QPointF &point, double dx, double dy)
{
    point.setX(point.x() + dx);
    point.setY(point.y() + dy);
}

void scalePoint(QPointF &point, double x0, double y0, double dx, double dy)
{
    point.setX(x0 + (point.x() - x0) * dx);
    point.setY(y0 + (point.y() - y0) * dy);
}

void rotatePoint(QPointF &point, double x0, double y0, double angleSin, double angleCos)
{
    double x = point.x(), y = point.y();
    point.setX(x0 + (x - x0) * angleCos + (y - y0) * angleSin);
    point.setY(y0 - (x - x0) * angleSin + (y - y0) * angleCos);
}



// Face processing functions

FaceProcessing::FaceProcessing()
{
    // сова
//    elements.push_back(generateRound(200, 100, 0, 0));
//    elements.push_back(generateRound(20, 10, -20, -30));
//    elements.push_back(generateRound(20, 10, 20, -30));

    elements.push_back({{0, 0}});

    elements.push_back(generateEllipse(50, 50, 0, 0));

    elements.push_back(generateEllipse(15, 5, -20, -17));
    elements.push_back(generateEllipse(15, 5, 20, -17));

    elements.push_back(generateTriangle(0, -10, 10, 10, -10, 10));
    elements.push_back(generateTriangle(-30, 15, 30, 15, 0, 35));

    elements.push_back(generateLine(0, -50, 0, -30));

    elements.push_back(generateLine(-10, ellipseUpPoint(-10, 50, 50, 0, 0),
                                    -20, -30));
    elements.push_back(generateLine(10, ellipseUpPoint(10, 50, 50, 0, 0),
                                    20, -30));

    elements.push_back(generateLine(-20, ellipseUpPoint(-20, 50, 50, 0, 0),
                                    -35, -25));
    elements.push_back(generateLine(20, ellipseUpPoint(20, 50, 50, 0, 0),
                                    35, -25));
    this->scale(0, 0, 2, 2);
    updated = false;

}


void FaceProcessing::move(double dx, double dy)
{
    prev_elements = elements;
    updated = true;

    for (QVector<QPointF> &figure: elements)
        for (QPointF &point: figure)
            movePoint(point, dx, dy);
}

void FaceProcessing::scale(double x0, double y0, double dx, double dy)
{
    prev_elements = elements;
    updated = true;

    for (QVector<QPointF> &figure: elements)
        for (QPointF &point: figure)
            scalePoint(point, x0, y0, dx, dy);
}

void FaceProcessing::rotate(double x0, double y0, double angle)
{
    prev_elements = elements;
    updated = true;

    double aSin = sin(angle);
    double aCos = cos(angle);
    for (QVector<QPointF> &figure: elements)
        for (QPointF &point: figure)
            rotatePoint(point, x0, y0, aSin, aCos);
}

void FaceProcessing::prev()
{
    if (updated)
    {
        elements = prev_elements;
    }
    updated = false;
}

QPointF FaceProcessing::center()
{
    return elements[0][0];
}
