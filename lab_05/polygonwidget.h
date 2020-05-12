#ifndef POLYGONWIDGET_H
#define POLYGONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPair>
#include <QTimer>
#include <QEventLoop>

#include <vector>
#include <utility>
#include <array>
#include <chrono>

struct DrawStatus
{
    bool modified = false;
    bool fixed = false;
    bool done = false;
    QPoint startPoint;
    QPoint lastPoint;
    QPoint prevPoint;
    size_t lastDrawTime;
};

struct DrawParams
{
    QColor fillColor = Qt::black;
    QColor backgroundColor = Qt::white;

};

struct DelayStatus
{
    bool hasDelay = false;
    int delayStep = 1;
    int status = 0;
};

class PolygonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PolygonWidget(QWidget *parent = nullptr);

    void setDelay(bool delay = true);
    void setColor(QColor color);
    void fill();
    void clear();
    void close();
    size_t getLastDrawTime();

signals:
    void newEdgeAdded(const QLine &);
    void edgesCleared();

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;



private:

    void delayRepaint();

    void drawLineTo(QPoint newPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    QPoint getPosition(QPoint &position);

    int findRightest();

    QImage image;
    QVector<QLine> edges;

    DrawStatus status;
    DrawParams drawParams;
    DelayStatus delayStatus;

};

#endif // POLYGONWIDGET_H
