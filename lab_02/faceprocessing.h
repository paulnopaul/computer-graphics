#ifndef FACEPROCESSING_H
#define FACEPROCESSING_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <cmath>
#include <utility>
#include <iostream>
#include <QPointF>

double ellipseDownPoint(double x, double a, double b, double x0, double y0);
double ellipseUpPoint(double x, double a, double b, double x0, double y0);

QVector<QPointF> generateEllipse(double a, double b, double x0, double y0, int point_count = 300);
QVector<QPointF> generateTriangle(double x0, double y0, double x1, double y1, double x2, double y2);
QVector<QPointF> generateLine(double x0, double y0, double x1, double y1);

void movePoint(QPointF &point, double dx, double dy);
void scalePoint(QPointF &point, double x0, double y0, double dx, double dy);
void rotatePoint(QPointF &point,  double x0, double y0, double angleSin, double angleCos);

class FaceProcessing
{
public:
    FaceProcessing();

    void rotate(double x0, double y0, double angle);
    void move(double dx, double dy);
    void scale(double x0, double y0, double dx, double dy);
    void prev();
    QPointF center();

    QVector<QVector<QPointF>> elements;
private:
    bool updated;
    QVector<QVector<QPointF>> prev_elements;
};

#endif // FACEPROCESSING_H
