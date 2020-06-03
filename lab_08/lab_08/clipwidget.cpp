#include "clipwidget.h"

using namespace std;

// ******* draw engine
void ClipDrawEngine::setPen(const QPen &_pen)
{
    pen = _pen;
}

// ******* line draw engine
void LineDrawEngine::clear()
{
    lines.clear();
}

QPoint LineDrawEngine::nextPoint(QPoint pos)
{
    if (mode == Mode::FIXED)
        return nextFixed(pos);
    else if (mode == Mode::PARALLEL)
        return nextParallel(pos);
    return pos;
}

QVector<QLine> LineDrawEngine::getLines()
{
    return lines;
}

QPoint LineDrawEngine::nextFixed(QPoint pos)
{
    if (firstPoint.y() != pos.y())
    {
        double tan = (double)fabs(firstPoint.x() - pos.x()) /
                (double)fabs(firstPoint.y() - pos.y());
        if (tan >= 1)
            pos = QPoint(pos.x(), firstPoint.y());
        else
            pos = QPoint(firstPoint.x(), pos.y());
    }
    else
        pos = QPoint(pos.x(), firstPoint.y());
    return pos;
}

QPoint LineDrawEngine::nextParallel(QPoint pos)
{
    int dxx = parallel_to.x1() * parallel_to.y2() -
            parallel_to.x2() * parallel_to.y1();
    int up_coef = (firstPoint.x() * parallel_to.dy() - dxx) / parallel_to.dx();
    int n = up_coef - firstPoint.y();
    pos.setY((pos.x() * parallel_to.dy() - dxx) / parallel_to.dx() - n);
    return pos;
}

void LineDrawEngine::finish(QPoint pos)
{
    lines.push_back(QLine(firstPoint, nextPoint(pos)));
}

void LineDrawEngine::mouseClick(QPoint pos)
{
    if (status == Status::DONE)
    {
        status = Status::MIDDLE;
        firstPoint = lastPoint = pos;
    }
    else if (status == Status::MIDDLE)
    {
        status = Status::DONE;
        finish(pos);
    }
}

void LineDrawEngine::mouseMove(QPoint pos)
{
    if (status == Status::DONE)
    {
       return;
    }
    else if (status == Status::MIDDLE)
    {
        lastPoint = nextPoint(pos);
    }
}

void LineDrawEngine::paintEvent(QPainter &p)
{
    p.setPen(pen);
    for (const QLine &line: lines)
        p.drawLine(line);
    if (status == Status::MIDDLE)
        p.drawLine(firstPoint, lastPoint);
}

void LineDrawEngine::setFixed(bool is_fixed)
{
    if (is_fixed)
        mode = Mode::FIXED;
    else
        mode= Mode::RANDOM;
}

// ******* polygon draw engine

void PolyDrawEngine::close()
{
    status = Status::DONE;
}

void PolyDrawEngine::clear()
{
    polygon.clear();
}

QPolygon PolyDrawEngine::getPolygon()
{
    return polygon;
}

void PolyDrawEngine::mouseMove(QPoint pos)
{
    if (status == Status::DONE)
    {
       return;
    }
    else if (status == Status::MIDDLE)
    {
        lastPoint = pos;
    }
}

void PolyDrawEngine::mouseClick(QPoint pos)
{
    if (status == Status::DONE)
    {
        status = Status::MIDDLE;
        polygon.push_back(pos);
        lastPoint = pos;
    }
    else if (status == Status::MIDDLE)
    {
        polygon.push_back(pos);
    }
}

void PolyDrawEngine::paintEvent(QPainter &p)
{
    p.setPen(pen);
    if (status != Status::DONE)
    {
        for (int i = 0; i < polygon.size() - 1; ++i)
            p.drawLine(polygon[i], polygon[i + 1]);
        p.drawLine(polygon.back(), lastPoint);
    }
    else
        p.drawPolygon(polygon);
}

// ******* clip widget

ClipWidget::ClipWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}


void ClipWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgba(255, 255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ClipWidget::drawGrid(QPainter &p)
{
    int step = 25;
    p.setPen(Qt::black);
    p.setFont(QFont("Helvetica", 10));
    for (int i = 0; i < this->width(); i += step)
    {
        p.drawLine(i, 0, i, 10);
        p.drawText(i + 3, 20, QString("%1").arg(i));
    }
    for (int i = 0; i < this->height(); i += step)
    {
        p.drawLine(0, i, 10, i);
        p.drawText(10, i - 3, QString("%1").arg(i));
    }
}

void ClipWidget::clear()
{
    clearFigures();
    clearImage();
}

void ClipWidget::clearFigures()
{
    clip_.clipped_lines.clear();
    draw_.polygon.clear();
    draw_.lines.clear();
}

int sgn(int a)
{
    return (a > 0) ? 1 : (a < 0 ? -1 : 0);
}

int ClipWidget::checkConvex(const QPolygon &pol)
{
    bool flag = true;
    QPoint vo = pol[0];
    QPoint vi = pol[0];
    QPoint vn = pol[0];

    QPoint p1(vi.x() - vo.x(), vi.y() - vo.y());
    QPoint p2(vn.x() - vi.x(), vn.y() - vi.y());

    int r = p1.x() * p2.y() - p2.x() * p1.y();
    int prev = sgn(r), cur;

    for (int i = 2; flag && i < pol.size() - 1; ++i)
    {
       vo = pol[i - 1];
       vi = pol[i];
       vn = pol[i + 1];

       p1.setX(vi.x() - vo.x());
       p1.setY(vi.y() - vo.y());

       p2.setX(vn.x() - vi.x());
       p2.setY(vn.y() - vi.y());

       r = p1.x() * p2.y() - p2.x() * p1.y();
       cur = sgn(r);
       if (cur != prev)
           flag = false;
       prev = cur;
    }
    vo = pol.back();
    vi = pol[0];
    vn = pol[1];

    p1.setX(vi.x() - vo.x());
    p1.setY(vi.y() - vo.y());

    p2.setX(vn.x() - vi.x());
    p2.setY(vn.y() - vi.y());

    r = p1.x() * p2.y() - p2.x() * p1.y();
    cur = sgn(r);
    if (cur != prev)
        flag = false;
    return flag * cur;
}

int scProduction(QPoint v1, QPoint v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

void ClipWidget::cyrusBeck(const QPolygon &polygon, QPoint p1, QPoint p2, int n)
{
    double tmin = 0, tmax = 1, t;
    QPoint dir(p2.x() - p1.x(),
               p2.y() - p1.y()), w, norm;
    for (int i = 0; i < polygon.size(); ++i)
    {
        w.setX(p1.x() - polygon[i].x());
        w.setY(p1.y() - polygon[i].y());

        if (i == polygon.size() - 1)
        {
            norm.setX(-n * (polygon[0].y() - polygon[i].y()));
            norm.setY(n * (polygon[0].x() - polygon[i].x()));
        }
        else
        {
            norm.setX(-n * (polygon[i + 1].y() - polygon[i].y()));
            norm.setY(n * (polygon[i + 1].x() - polygon[i].x()));
        }
        int dsc = scProduction(dir, norm);
        int wsc = scProduction(w, norm);

        if (dsc == 0)
        {
            if (wsc < 0)
                return;
        }
        else
        {
            t = -(double)wsc/dsc;
            if (dsc > 0)
            {
                if (t > 1)
                    return;
                tmin = max(tmin, t);
            }
            else if (dsc < 0)
            {
                if (t < 0)
                    return;
                tmax = min(tmax, t);
            }
        }
    }
    if (tmin <= tmax)
        clip_.clipped_lines.push_back(QLine(p1.x() + (p2.x() - p1.x()) * tmax,
                                            p1.y() + (p2.y() - p1.y()) * tmax,
                                            p1.x() + (p2.x() - p1.x()) * tmin,
                                            p1.y() + (p2.y() - p1.y()) * tmin));
}

void ClipWidget::clip()
{
    int n = checkConvex(draw_.polygon.getPolygon());
    if (n == 0)
        for (QLine &line: draw_.lines.getLines())
            cyrusBeck(draw_.polygon.getPolygon(), line.p1(), line.p2(), 1);
    repaintImage();
}

void ClipWidget::setLineColor(QColor color)
{
    draw_.lines.setPen(QPen(color));
}

void ClipWidget::setRectColor(QColor color)
{
    draw_.polygon.setPen(QPen(color));
}

void ClipWidget::setClipColor(QColor color)
{
    clip_.color = color;
}

void ClipWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
            int newWidth = qMax(width() + 128, image.width());
            int newHeight = qMax(height() + 128, image.height());
            resizeImage(&image, QSize(newWidth, newHeight));
            update();
    }
    QWidget::resizeEvent(event);
}

void ClipWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect drawRect = this->rect();
    p.drawImage(drawRect, image, drawRect);
    drawGrid(p);

    draw_.lines.paintEvent(p);
    draw_.polygon.paintEvent(p);
}

void ClipWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key::Key_Escape:
        break;
    case Qt::Key::Key_P:
        draw_.mode = DrawMode::POLYGON;
        break;
    case Qt::Key::Key_L:
        draw_.mode = DrawMode::LINE;
        break;
    case Qt::Key::Key_C:
        draw_.polygon.close();
        break;
    case Qt::Key::Key_Return:
         clip();
        break;
    case Qt::Key::Key_Backspace:
        clear();
        break;
    case Qt::Key::Key_Shift:
        draw_.lines.setFixed(true);
        break;
    case Qt::Key::Key_N: // TODO
        break;
    }
    repaint();
}

void ClipWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key::Key_Shift:
        draw_.lines.setFixed(false);
        break;
    }
}

double pointToLineDistance(QPoint p, QPoint l1, QPoint l2)
{
    QPoint v = l2 - l1;
    QPoint w = p - l1;
    int c1 = scProduction(v, w);
    if (c1 <= 0)
        return sqrt((p.x() - l1.x()) * (p.x() - l1.x()) +
                    (p.y() - l1.y()) * (p.y() - l1.y()));

    int c2 = scProduction(v, v);
    if (c2 <= c1)
        return sqrt((p.x() - l2.x()) * (p.x() - l2.x()) +
                    (p.y() - l2.y()) * (p.y() - l2.y()));
    double b = (double)c1 / c2;
    QPoint pb = l1 + b * v;
    return sqrt((p.x() - pb.x()) * (p.x() - pb.x()) +
                (p.y() - pb.y()) * (p.y() - pb.y()));
}

QLine ClipWidget::nearestEdge(QPoint pos)
{
    QPolygon pol(draw_.polygon.getPolygon());
    QLine nearest(pol[0], pol.back());
    double distance = pointToLineDistance(pos, pol[0], pol.back());
    for (int i = 0; i < pol.size() - 1; ++i)
    {
        double curDist = pointToLineDistance(pos, pol[i], pol[i + 1]);
        if (curDist < distance)
        {
            distance = curDist;
            nearest.setPoints(pol[i], pol[i + 1]);
        }
    }
    return nearest;
}

void ClipWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->setFocus();
    QPoint pos = event->pos();
    if (draw_.mode == DrawMode::LINE)
        draw_.lines.mouseMove(pos);
    else if (draw_.mode == DrawMode::POLYGON)
        draw_.polygon.mouseMove(pos);
    repaint();
}

void ClipWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (draw_.mode == DrawMode::LINE)
        draw_.lines.mouseClick(pos);
    else if (draw_.mode == DrawMode::POLYGON)
        draw_.polygon.mouseClick(pos);
    repaint();
}

void ClipWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
}

void ClipWidget::clearImage()
{
    image.fill(qRgba(255, 255, 255, 255));
    repaint();
}

void ClipWidget::repaintImage()
{
    clearImage();
    QPainter p(&image);
    repaint();
}



