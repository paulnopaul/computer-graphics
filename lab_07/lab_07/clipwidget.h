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
    RECT,
    LINE
};

enum class RectModeStatus
{
    FIRST_POINT,
    SECOND_POINT
};

struct RectModeInfo
{
    RectModeStatus status = RectModeStatus::FIRST_POINT;
    QPoint firstPoint = QPoint(0, 0);
    QPoint lastPoint = QPoint(0, 0);
    QColor color = Qt::black;
};

enum class LineModeStatus
{
    FIRST_POINT,
    SECOND_POINT
};

struct LineModeInfo
{
    LineModeStatus status = LineModeStatus::FIRST_POINT;
    QPoint firstPoint = QPoint(0, 0);
    QPoint lastPoint = QPoint(0, 0);
    QColor color = Qt::black;
    bool is_fixed = false;
};

struct DrawInfo
{
    DrawMode mode = DrawMode::RECT;
    RectModeInfo rectInfo;
    LineModeInfo lineInfo;
};

struct ClipInfo
{
    QRect clipRect;
    QVector<QLine> lines;
    QVector<QLine> clipped_lines;
    QColor color = Qt::red;
};

void twoPointRect(QPainter p, QPoint first, QPoint second);

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

    // **** Functions for clipping ****

    using Code = std::array<char, 4>;

    Code computeCode(QPoint point,
                    int xmin, int ymin,
                    int xmax, int ymax);

    int visible(Code t1,
                Code t2);

    void cohenSutherland(int xmin, int ymin,
                         int xmax, int ymax,
                         QPoint p1, QPoint p2);

    // **** Draw functions ****
    void lineMousePress(QPoint pos);
    void lineMouseRelease(QPoint pos);
    void lineMouseMove(QPoint pos);
    void linePaint(QPainter &p);

    QPoint lineSecondPoint(QPoint pos);

    void rectMousePress(QPoint pos);
    void rectMouseRelease(QPoint pos);
    void rectMouseMove(QPoint pos);
    void rectPaint(QPainter &p);

    void drawGrid(QPainter &p);
    void addLine(QPoint start, QPoint end);
    void updateClipRect(QPoint start, QPoint end);

    void clearFigures();

    void resizeImage(QImage *image, const QSize &newSize);
    QImage image;

    ClipInfo clip_;
    DrawInfo draw_;
};

#endif // CLIPWIDGET_H
