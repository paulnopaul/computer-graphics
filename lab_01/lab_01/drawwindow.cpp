#include "drawwindow.h"
#include <QPainter>
#include <iostream>
#include <QDebug>
#include <vector>

DrawWindow::DrawWindow(QWidget *parent)
    : QWidget(parent)
{
}

void DrawWindow::addPoint(QPoint p)
{
    this->points.push_back(p);
}

void DrawWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (QPoint p: points)
        painter.drawPoint(p);
}

DrawWindow::~DrawWindow()
{
}
