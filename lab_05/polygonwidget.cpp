#include "polygonwidget.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int sgn(int x)
{
    return (x > 0) ? 1 : -1 * (x < 0);
}

void drawLine(QPainter &p, QPoint startPoint, QPoint endPoint)
{
    // DDA alghorithm
    if ((abs(startPoint.x() - endPoint.x()) == 0) &&
                (fabs(startPoint.y() - endPoint.y()) == 0))
    {
        p.drawPoint(startPoint);
        return;
    }
    double dx = endPoint.x() - startPoint.x();
    double dy = endPoint.y() - startPoint.y();
    double l = std::max(fabs(dx), fabs(dy));

    dx = dx / l;
    dy = dy / l;

    double x = startPoint.x();
    double y = startPoint.y();

    for (int i = 0; i <= l; i++)
    {
        p.drawPoint(x, y);
        x = x + dx;
        y = y + dy;
    }
}

PolygonWidget::PolygonWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMouseTracking(true);
}

void PolygonWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
            int newWidth = qMax(width() + 128, image.width());
            int newHeight = qMax(height() + 128, image.height());
            resizeImage(&image, QSize(newWidth, newHeight));
            update();
        }
        QWidget::resizeEvent(event);
}


QPoint PolygonWidget::getPosition(QPoint &position)
{
    if (status.fixed)
    {
        if (status.prevPoint.y() != position.y())
        {
            double tan = (double)fabs(status.prevPoint.x() - position.x()) /
                    (double)fabs(status.prevPoint.y() - position.y());
            if (tan >= 1)
                position = QPoint(position.x(), status.prevPoint.y());
            else
                position = QPoint(status.prevPoint.x(), position.y());
        }
        else
            position = QPoint(position.x(), status.prevPoint.y());
    }
    return position;
}

void drawLines(QPainter &p, const QVector<QLine> &lines)
{
    for (const QLine &line : lines)
        drawLine(p, line.p1(), line.p2());

}

void PolygonWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(drawParams.fillColor);
    QRect drawRect = this->rect();
    p.drawImage(drawRect, image, drawRect);
    drawLines(p, edges);
    if (!status.done && status.modified)
    {
        QPoint spoint = getPosition(status.lastPoint);
        drawLine(p, status.prevPoint, spoint);
        p.drawText(10, 30, QString("(%1, %2)").arg(spoint.x()).arg(spoint.y()));
    }
}


void PolygonWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint newPoint = event->pos();
    if (!status.modified)
    {
        status.prevPoint = status.startPoint = newPoint;
        status.modified = true;
    }
    else
    {
        drawLineTo(getPosition(newPoint));
        status.prevPoint = newPoint;
    }
}


void PolygonWidget::setDelay(bool _delay)
{
    delayStatus.hasDelay = _delay;
}

void PolygonWidget::setColor(QColor color)
{
    drawParams.fillColor = color;
}

void PolygonWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(drawParams.backgroundColor.rgba());
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PolygonWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Return)
    {
        if (!status.done)
            close();
        else
            fill();
    }
    if (event->key() == Qt::Key::Key_Shift)
        status.fixed = true;
    if (event->key() == Qt::Key::Key_Backspace)
        clear();
}

void PolygonWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Shift)
        status.fixed = false;
}

void PolygonWidget::close()
{
    drawLineTo(status.startPoint);
    status.modified = false;
    status.done = true;
    update();
}

void PolygonWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!status.done)
    {
        setFocus();
        status.lastPoint = event->pos();
        update();
    }
}

void PolygonWidget::clear()
{
    image.fill(drawParams.backgroundColor.rgba());
    status.modified = false;
    status.done = false;
    edges.clear();
    update();

    emit edgesCleared();
}

void PolygonWidget::drawLineTo(QPoint newPoint)
{
    if (!status.done)
    {
//        QPainter p(&image);
//        p.setPen(drawParams.fillColor);
//        drawLine(p, status.prevPoint, newPoint);
//        this->update();

        edges.push_back(QLine(status.prevPoint, newPoint));
        emit newEdgeAdded(edges.last());
    }
}

int PolygonWidget::findRightest()
{
    int max_x = edges[0].x1();
    for (const QLine &line :edges)
        max_x = max(max_x, max(line.x1(), line.x2()));
    return max_x;
}

void PolygonWidget::delayRepaint()
{
    if (delayStatus.hasDelay)
    {

        if (delayStatus.status >= delayStatus.delayStep)
        {
            QEventLoop loop;
            QTimer::singleShot(0, &loop, SLOT(quit()));
            loop.exec();
            delayStatus.status = 0;
            repaint();
        }
        else
            ++delayStatus.status;
    }
}


void PolygonWidget::fill()
{

    steady_clock::time_point start = steady_clock::now();
    int xm = findRightest();
    for (QLine line: edges)
    {
        if (line.y1() == line.y2())
            continue;

        if (line.y1() > line.y2())
            line.setLine(line.x2(), line.y2(), line.x1(), line.y1());

        int y = line.y1();
        int end_y = line.y2();
        double start_x = line.x1();
        double dx = (double)line.dx() / line.dy();

        while (y < end_y)
        {
            int x = start_x;
            while (x < xm)
            {
                QColor col = QColor(image.pixel(x, y));
                if  (col == drawParams.backgroundColor)
                    col = drawParams.fillColor;
                else
                    col = drawParams.backgroundColor;
                image.setPixel(x, y, col.rgba());
                x++;
            }
            start_x += dx;

            delayRepaint();
            y++;
        }
    }
    steady_clock::time_point end = steady_clock::now();
    status.lastDrawTime = duration_cast<milliseconds>(end - start).count();
    repaint();
}

size_t PolygonWidget::getLastDrawTime()
{
    return status.lastDrawTime;
}



