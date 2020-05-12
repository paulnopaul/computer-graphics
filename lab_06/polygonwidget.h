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
#include <QStack>
#include <QSet>

#include <vector>
#include <utility>
#include <array>
#include <chrono>

enum class DrawMode
{
    POLYGON,
    CURVE
};

struct DrawStatus
{
    DrawMode mode = DrawMode::POLYGON;
    bool fixed = false;
    bool inProgress = false;
    bool done = false;
    bool isFillPointChoosing = false;

    QPoint startPoint;
    QPoint lastPoint;
    QPoint prevPoint;
    size_t lastDrawTime;
};

struct DrawParams
{
    QColor backgroundColor = Qt::white;
    QColor lineColor = Qt::black;
};

struct FillParams
{
    QColor fillColor = Qt::red;
    QPoint fillPoint = QPoint(0, 0);
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
    void setPolygon(bool isPolygon = true);
    void setLineColor(QColor color);
    void setFillColor(QColor color);
    void fill();
    void clear();
    void close();
    void startPointEvent();
    size_t getLastDrawTime();
    QPoint getLastFillPoint();

signals:
    void newEdgeAdded(const QLine &);
    void edgesCleared();
    void newFillPointCoords(QPoint newPoint);
    void figureFilled();

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


private:

    void delayRepaint();

    void drawLineTo(QPoint newPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    QPoint getPosition(QPoint position);

    QImage image;
    QVector<QLine> edges;

    DrawStatus status;
    DrawParams drawParams;
    FillParams fillParams;
    DelayStatus delayStatus;

};

#endif // POLYGONWIDGET_H
