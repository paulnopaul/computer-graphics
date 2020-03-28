#ifndef PIXELRECTDRAW_H
#define PIXELRECTDRAW_H

#include <QWidget>
#include <QPainter>

#include <cmath>
#include <algorithm>
#include <utility>

enum class AlgoType
{
    SMOOTH_BRESENHAM,
    BRESENHAM,
    WOO,
    DDA
};

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

class PixelLineDraw : public QWidget
{
    Q_OBJECT
public:
    explicit PixelLineDraw(QWidget *parent = nullptr);
    void drawLine(QPointF start, QPointF end, AlgoType _type);
private:
    void paintEvent(QPaintEvent *event) override;

    void drawBresenham(QPainter &p);

//    void drawBresenhamSmooth(QPainter &p);

    void drawDDA(QPainter &p);

//    void drawWoo(QPainter &p);

    AlgoType type;

    QPointF startPoint;
    QPointF endPoint;

};

#endif // PIXELRECTDRAW_H
