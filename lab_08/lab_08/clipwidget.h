#ifndef CLIPWIDGET_H
#define CLIPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QLine>

#include <iostream>
#include <array>
#include <cmath>

enum class DrawMode
{
    POLYGON,
    LINE
};

struct ClipInfo
{
    QVector<QLine> clipped_lines;
    QColor color = Qt::red;
};

void twoPointRect(QPainter p, QPoint first, QPoint second);

int scProduction(QPoint v1, QPoint v2);

double pointToLineDistance(QPoint p, QPoint l1, QPoint l2);

class ClipDrawEngine
{
public:
    enum class Status
    {
        START,
        DONE,
        MIDDLE
    };
    ClipDrawEngine() = default;
    void setPen(const QPen &_pen);
    virtual void clear() = 0;
    virtual void mouseClick(QPoint pos) = 0;
    virtual void mouseMove(QPoint pos) = 0;
    virtual void paintEvent(QPainter &p) = 0;
protected:
    Status status = Status::DONE;
    QPoint firstPoint;
    QPoint lastPoint;
    QPen pen;
};

class LineDrawEngine : public ClipDrawEngine
{
public:
    enum class Mode
    {
        RANDOM,
        FIXED,
        PARALLEL
    };
    LineDrawEngine() = default;

    void mouseClick(QPoint pos) override;
    void mouseMove(QPoint pos) override;
    void paintEvent(QPainter &p) override;
    void clear() override;

    void setFixed(bool is_fixed);
    QVector<QLine> getLines();
private:
    QPoint nextFixed(QPoint pos);
    QPoint nextParallel(QPoint pos);
    QPoint nextPoint(QPoint pos);
    void finish(QPoint pos);
    void updateParallel(QPolygon polygon);
    QLine parallel_to;
    QVector<QLine> lines;
    Mode mode = Mode::RANDOM;
};

class PolyDrawEngine : public ClipDrawEngine
{
public:
    enum class Mode
    {
        RANDOM,
        RECT
    };
    PolyDrawEngine() = default;
    QPolygon getPolygon();
    void mouseClick(QPoint pos) override;
    void mouseMove(QPoint pos) override;
    void paintEvent(QPainter &p) override;
    void close();
    void clear() override;
private:
    QPolygon polygon;
    Mode mode = Mode::RANDOM;
};

struct Drawer
{
    DrawMode mode = DrawMode::POLYGON;
    LineDrawEngine lines;
    PolyDrawEngine polygon;
};

/* Widget class */

class ClipWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClipWidget(QWidget *parent = nullptr);
    void clip();
    void clear();
public slots:
    void setLineColor(QColor color);
    void setRectColor(QColor color);
    void setClipColor(QColor color);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void clearImage();
    void repaintImage();
private:

    int checkConvex(const QPolygon &pol);

    void cyrusBeck(QPolygon &polygon, QPoint p1, QPoint p2, int n);

    // **** Draw functions ****
    QLine nearestEdge(QPoint pos);

    void polyMousePress(QPoint pos);
    void polyMouseRelease(QPoint pos);
    void polyMouseMove(QPoint pos);
    void polyPaint(QPainter &p);

    void drawGrid(QPainter &p);
    void updatePolygon();

    void clearFigures();

    void resizeImage(QImage *image, const QSize &newSize);
    QImage image;

    ClipInfo clip_;
    Drawer draw_;
};

#endif // CLIPWIDGET_H
