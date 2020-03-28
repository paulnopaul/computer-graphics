#ifndef MYDRAW_H
#define MYDRAW_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <QString>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

#include "faceprocessing.h"

class MyDraw : public QWidget
{
public:
    MyDraw(QWidget *parent);
    void move(double dx, double dy);
    void scale(double x0, double y0, double dx, double dy);
    void rotate(double x0, double y0, double r);
    void draw();
    void prev();
private:
    void paintEvent(QPaintEvent *event = nullptr) override;
    FaceProcessing fp;
};

#endif // MYDRAW_H
