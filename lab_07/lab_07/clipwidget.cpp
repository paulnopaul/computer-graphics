#include "clipwidget.h"

using namespace std;


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
    int step = 50;
    p.setPen(Qt::black);
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
    clip_.lines.clear();
    clip_.clipped_lines.clear();
}

ClipWidget::Code ClipWidget::computeCode(QPoint point,
                            int xmin, int ymin,
                            int xmax, int ymax)
{
    Code code = {0, 0, 0, 0};

    if (point.x() < xmin)
        code[0] = 1;
    else if (point.x() > xmax)
        code[1] = 1;
    if (point.y() < ymin)
        code[2] = 1;
    else if (point.y() > ymax)
        code[3] = 1;
    return code;
}

int ClipWidget::visible(Code t1,
                        Code t2)
{
    int vis = 2;
    if (t1[0] + t1[1] + t1[2] + t1[3] == 0 &&
        t2[0] + t2[1] + t2[2] + t2[3] == 0)
        vis = 1;
    else if ((t1[0] & t2[0]) |
             (t1[1] & t2[1]) |
             (t1[2] & t2[2]) |
             (t1[3] & t2[3]))
        vis = 0;
    return vis;
}

void ClipWidget::cohenSutherland(int xmin, int ymin,
                                 int xmax, int ymax,
                                 QPoint p1, QPoint p2)
{
    int fl = 1;
    double m = -1;
    int o[] = {xmin, xmax, ymin, ymax};

    if (p1.x() == p2.x())
        fl = -1;
    else
        m = (double)(p2.y() - p1.y()) / (p2.x() - p1.x());

    if (m == 0)
        fl = 0;


    for (int i = 0; i < 4; ++i)
    {
        Code t1 = computeCode(p1, xmin, ymin, xmax, ymax);
        Code t2 = computeCode(p2, xmin, ymin, xmax, ymax);

        int v = visible(t1, t2);

        if (v == 1)
            break;
        else if (!v)
            return;

        if (t1[i] == t2[i])
            continue;

        if (!t1[i])
            swap(p1, p2);

        if (fl != -1)
        {
            if (i < 2)
            {
                p1.setY(m * (o[i] - p1.x()) + p1.y());
                p1.setX(o[i]);
                continue;
            }
            else
                p1.setX((1 / m) * (o[i] - p1.y()) + p1.x());
        }
        p1.setY(o[i]);
    }
    clip_.clipped_lines.push_back(QLine(p1, p2));
    repaintImage();
}

void ClipWidget::clip()
{
    int xmin = clip_.clipRect.x();
    int ymin = clip_.clipRect.y();
    int xmax = xmin + clip_.clipRect.width();
    int ymax = ymin + clip_.clipRect.height();
    for (const QLine &line: clip_.lines)
    {
        cohenSutherland(xmin, ymin, xmax, ymax, line.p1(), line.p2());
    }
}

void ClipWidget::setLineColor(QColor color)
{
    draw_.lineInfo.color = color;
}

void ClipWidget::setRectColor(QColor color)
{
    draw_.rectInfo.color = color;
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
    if (draw_.mode == DrawMode::LINE)
        linePaint(p);
    else if (draw_.mode == DrawMode::RECT)
        rectPaint(p);
    drawGrid(p);
}

void ClipWidget::linePaint(QPainter &p)
{
    if (draw_.lineInfo.status == LineModeStatus::SECOND_POINT)
    {
        p.setPen(draw_.lineInfo.color);
        p.drawLine(draw_.lineInfo.firstPoint, draw_.lineInfo.lastPoint);
    }
}

void ClipWidget::rectPaint(QPainter &p)
{
    if (draw_.rectInfo.status == RectModeStatus::SECOND_POINT)
    {
        p.setPen(draw_.rectInfo.color);
        p.drawRect(QRect(draw_.rectInfo.firstPoint, draw_.rectInfo.lastPoint));
    }
}

void ClipWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key::Key_Escape:
        break;
    case Qt::Key::Key_R:
        draw_.mode = DrawMode::RECT;
        break;
    case Qt::Key::Key_L:
        draw_.mode = DrawMode::LINE;
        break;
    case Qt::Key::Key_Return:
        clip();
        break;
    case Qt::Key::Key_Backspace:
        clear();
        break;
    case Qt::Key::Key_Shift:
        draw_.lineInfo.is_fixed = true;
        break;
    }
}

void ClipWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key::Key_Shift:
        draw_.lineInfo.is_fixed = false;
        break;
    }
}

void ClipWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->setFocus();
    QPoint pos = event->pos();
    if (draw_.mode == DrawMode::LINE)
        lineMouseMove(pos);
    else if (draw_.mode == DrawMode::RECT)
        rectMouseMove(pos);
}

QPoint ClipWidget::lineSecondPoint(QPoint pos)
{
    if (draw_.lineInfo.is_fixed)
    {
        if (draw_.lineInfo.firstPoint.y() != pos.y())
        {
            double tan = (double)fabs(draw_.lineInfo.firstPoint.x() - pos.x()) /
                    (double)fabs(draw_.lineInfo.firstPoint.y() - pos.y());
            if (tan >= 1)
                pos = QPoint(pos.x(), draw_.lineInfo.firstPoint.y());
            else
                pos = QPoint(draw_.lineInfo.firstPoint.x(), pos.y());
        }
        else
            pos = QPoint(pos.x(), draw_.lineInfo.firstPoint.y());
    }
    return pos;
}

void ClipWidget::lineMouseMove(QPoint pos)
{
    if (draw_.lineInfo.status == LineModeStatus::SECOND_POINT)
    {
        draw_.lineInfo.lastPoint = lineSecondPoint(pos);
        repaint();
    }
}

void ClipWidget::rectMouseMove(QPoint pos)
{
    if (draw_.rectInfo.status == RectModeStatus::SECOND_POINT)
    {
        draw_.rectInfo.lastPoint = pos;
        repaint();
    }
}

void ClipWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (draw_.mode == DrawMode::LINE)
        lineMousePress(pos);
    else if (draw_.mode == DrawMode::RECT)
        rectMousePress(pos);
}

void ClipWidget::lineMousePress(QPoint pos)
{
    draw_.lineInfo.firstPoint = pos;
    draw_.lineInfo.status = LineModeStatus::SECOND_POINT;
}

void ClipWidget::rectMousePress(QPoint pos)
{
    draw_.rectInfo.firstPoint = pos;
    draw_.rectInfo.status = RectModeStatus::SECOND_POINT;
}

void ClipWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (draw_.mode == DrawMode::LINE)
        lineMouseRelease(pos);
    else if (draw_.mode == DrawMode::RECT)
        rectMouseRelease(pos);
}

void ClipWidget::lineMouseRelease(QPoint pos)
{
    if (draw_.lineInfo.status == LineModeStatus::SECOND_POINT)
    {
        addLine(draw_.lineInfo.firstPoint, lineSecondPoint(pos));
        draw_.lineInfo.status = LineModeStatus::FIRST_POINT;
    }
}

void ClipWidget::rectMouseRelease(QPoint pos)
{
    if (draw_.rectInfo.status == RectModeStatus::SECOND_POINT)
    {
        updateClipRect(draw_.rectInfo.firstPoint, pos);
        draw_.rectInfo.status = RectModeStatus::FIRST_POINT;
    }
}

void ClipWidget::addLine(QPoint start, QPoint end)
{
    clip_.lines.push_back(QLine(start, end));
    QPainter p(&image);
    p.setPen(draw_.lineInfo.color);
    p.drawLine(start, end);

}

void ClipWidget::updateClipRect(QPoint start, QPoint end)
{
    clip_.clipRect = QRect(start, end);
    repaintImage();
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

    p.setPen(draw_.lineInfo.color);
    for (const QLine &line: clip_.lines)
        p.drawLine(line);

    p.setPen(draw_.rectInfo.color);
    p.drawRect(clip_.clipRect);

    p.setPen(QPen(QBrush(clip_.color), 2));
    for (const QLine &line: clip_.clipped_lines)
        p.drawLine(line);

    repaint();
}



