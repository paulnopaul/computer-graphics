#ifndef PIXELRECTDRAW_H
#define PIXELRECTDRAW_H

#include <QWidget>
#include <QPainter>

#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

enum class AlgoType
{
    SMOOTH_BRESENHAM,
    FLOAT_BRESENHAM,
    INT_BRESENHAM,
    WU,
    DDA,
    LIBRARY,
    DEFAULT
};

struct MyLine
{
    MyLine(QPoint _start, QPoint _end, AlgoType _type, QColor _color) :
        start(_start),
        end(_end),
        type(_type),
        color(_color)
    {};
    QPoint start;
    QPoint end;
    AlgoType type;
    QColor color;
};

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T> int Integer(T val)
{
    return floor(val);
}

void rotPoint(double rc, double rs, QPoint &endPoint, QPoint startPoint);

class PixelLineDraw : public QWidget
{
    Q_OBJECT
public:
    explicit PixelLineDraw(QWidget *parent = nullptr);
    void drawLine(QPoint start, QPoint end, AlgoType _type, QColor color);
    void drawDifferentLines(double rotateAngle, AlgoType _type, QColor color); // step in radians
    void clear();
private:

    // basic setup funtions
    void paintEvent(QPaintEvent *event) override;
    void drawScale(QPainter &p);

    // Set Line Vector Functions
    void drawOneLine(QPainter &p, MyLine &line);

    // Draw Line Vector

    void drawFloatBresenham(QPainter &p);

    void drawIntBresenham(QPainter &p);

    void drawSmoothBresenham(QPainter &p);

    void drawDDA(QPainter &p);

    void drawWu(QPainter &p);

    void drawLibrary(QPainter &p);

    void drawPoint(QPainter &p, double x, double y, double intensivity);

    void drawPointInt(QPainter &p, int x, int y, int intensivity);

    AlgoType type;
    QPoint startPoint;
    QPoint endPoint;
    QColor mainColor;

    vector<MyLine> lines;
};

#endif // PIXELRECTDRAW_H
