#ifndef PIXELDRAWER_H
#define PIXELDRAWER_H

#include <QWidget>
#include <QPainter>

#include <vector>
#include <iterator>
#include <cstdlib>

#include "ellipse.h"
#include "circle.h"

class PaintObject
{
public:

    PaintObject(const Ellipse &ellipse, const QColor color);

    std::vector<QPoint>::iterator begin();

    std::vector<QPoint>::iterator end();

    const std::vector<QPoint>::const_iterator begin() const;

    const std::vector<QPoint>::const_iterator end() const;

    QColor GetColor() const;

    const Ellipse& GetEllipse() const;
private:
    Ellipse ellipse_;
    QColor color_;
};

using PaintObjects = std::vector<PaintObject>;

class PixelDrawer : public QWidget
{
    Q_OBJECT
private:
    void paintEvent(QPaintEvent *event) override;

    static void DrawObject(QPainter &painter, const PaintObject &object);

    void DrawObjects(QPainter &painter);

    void DrawScale(QPainter &painter, int step);

public:
    explicit PixelDrawer(QWidget *parent = nullptr);

    void Clear();

    void Add(const PaintObject &object);

    void AddEllipse(const Ellipse &ellipse, QColor color);

    void Draw();
private:
    PaintObjects objects;
};

#endif // PIXELDRAWER_H
