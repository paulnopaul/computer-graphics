#include "polygonwidget.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

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


QPoint PolygonWidget::getPosition(QPoint position)
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

void PolygonWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(this->rect(), image, this->rect());
    p.drawText(10, 30, QString("(%1, %2)").arg(status.lastPoint.x()).
                                           arg(status.lastPoint.y()));
    p.setPen(drawParams.lineColor);
    if (status.isFillPointChoosing)
        p.drawEllipse(status.lastPoint + QPoint(-2, -2), 4, 4);
    else if (status.inProgress && status.mode == DrawMode::POLYGON)
        p.drawLine(status.prevPoint, status.lastPoint);
}

void PolygonWidget::setDelay(bool _delay)
{
    delayStatus.hasDelay = _delay;
}

void PolygonWidget::setLineColor(QColor color)
{
    drawParams.lineColor = color;
}

void PolygonWidget::setFillColor(QColor color)
{
    fillParams.fillColor = color;
}

void PolygonWidget::setPolygon(bool isPolygon)
{
    status.mode = isPolygon ? DrawMode::POLYGON : DrawMode::CURVE;
}

void PolygonWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Return)
    {
        if (status.inProgress)
            close();
        else
            fill();
    }
    if (event->key() == Qt::Key::Key_Shift)
        status.fixed = true;
    if (event->key() == Qt::Key::Key_Backspace)
        clear();
    if (event->key() == Qt::Key::Key_Space)
        startPointEvent();
    repaint();
}

void PolygonWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Shift)
        status.fixed = false;
    repaint();
}

void PolygonWidget::close()
{
    status.inProgress = false;
    drawLineTo(status.startPoint);
    repaint();
}

void PolygonWidget::mouseMoveEvent(QMouseEvent *event)
{
    setFocus();
    status.lastPoint = getPosition(event->pos());
    if (status.mode == DrawMode::CURVE && status.inProgress)
        drawLineTo(status.lastPoint);
    repaint();
}

void PolygonWidget::mousePressEvent(QMouseEvent *event)
{
    status.lastPoint = getPosition(event->pos());
    if (status.isFillPointChoosing)
    {
        fillParams.fillPoint = status.lastPoint;
        emit newFillPointCoords(fillParams.fillPoint);
        status.isFillPointChoosing = false;
    }
    else if (!status.inProgress)
    {
        status.startPoint = status.lastPoint;
        status.prevPoint = status.lastPoint;
        status.inProgress = true;
    }
    else if (status.mode == DrawMode::POLYGON)
        drawLineTo(status.lastPoint);
    repaint();
}


void PolygonWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (status.mode == DrawMode::CURVE && status.inProgress)
    {
        drawLineTo(status.startPoint);
        status.inProgress = false;
    }
    repaint();
}

void PolygonWidget::clear()
{
    this->image.fill(drawParams.backgroundColor.rgba());

    edges.clear();
    emit edgesCleared();

    repaint();
}

void PolygonWidget::drawLineTo(QPoint newPoint)
{
    QPainter p(&image);
    p.setPen(drawParams.lineColor);
    p.drawLine(status.prevPoint, newPoint);
    edges.push_back(QLine(status.prevPoint, newPoint));
    if (status.mode == DrawMode::POLYGON)
        emit newEdgeAdded(QLine(status.prevPoint, newPoint));
    status.prevPoint = newPoint;
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


void PolygonWidget::startPointEvent()
{
    status.isFillPointChoosing = true;
}


void PolygonWidget::fill()
{

    steady_clock::time_point start = steady_clock::now();
    QStack<QPoint> points;
    points.push(fillParams.fillPoint); // запись в стек начальной вершины
    while  (!points.empty())
    {
        QPoint currentPoint = points.pop();
        int x = currentPoint.x(), y = currentPoint.y(), lx, rx;

        // закраска пикселей слева от затравочной точки и поиск крайней левой
        // точки
        for (lx = x; image.pixel(lx, y) != drawParams.lineColor.rgba() &&
             image.pixel(lx, y) != fillParams.fillColor.rgba(); --lx)
            image.setPixel(lx, y, fillParams.fillColor.rgba());
        ++lx;

        // закраска пикселей справа от затравочной точки и поиск крайней правой
        // точки
        for (rx = x + 1; image.pixel(rx, y) != drawParams.lineColor.rgba() &&
             image.pixel(rx, y) != fillParams.fillColor.rgba(); ++rx)
            image.setPixel(rx, y, fillParams.fillColor.rgba());
        --rx;

        delayRepaint();
        y++;
        x = lx;
        bool f;
        while (x <= rx) // поиск затравочных точек в верхней строке
        {
            f = false;
            while (image.pixel(x, y) != drawParams.lineColor.rgba() &&
                   image.pixel(x, y) != fillParams.fillColor.rgba())
            {
                if (!f)
                    f = true;
                x++;
            }
            if (f)
            {
                if (x == rx && image.pixel(x, y) != drawParams.lineColor.rgba() &&
                        image.pixel(x, y) != fillParams.fillColor.rgba())
                        points.push(QPoint(x, y));
                else
                        points.push(QPoint(x - 1, y));
                f = false;
            }
            ++x;
        }

        y -= 2;

        x = lx;
        while (x <= rx) // поиск затравочных точек в нижней строке
        {
            f = false;
            while (image.pixel(x, y) != drawParams.lineColor.rgba() &&
                   image.pixel(x, y) != fillParams.fillColor.rgba())
            {
                if (!f)
                    f = true;
                x++;
            }
            if (f)
            {
                if (x == rx && image.pixel(x, y) != drawParams.lineColor.rgba() &&
                        image.pixel(x, y) != fillParams.fillColor.rgba())
                        points.push(QPoint(x, y));
                else
                        points.push(QPoint(x - 1, y));
                f = false;
            }
            ++x;
        }
    }
    steady_clock::time_point end = steady_clock::now();
    status.lastDrawTime = duration_cast<milliseconds>(end - start).count();
    repaint();
    emit figureFilled();
}

size_t PolygonWidget::getLastDrawTime()
{
    return status.lastDrawTime;
}



