#include "drawwindow.h"
#include <QPainter>
#include <iostream>
#include <QDebug>

DrawWindow::DrawWindow(QWidget *parent)
    : QWidget(parent)
{
}

void DrawWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(0, 0, width() - 1, height() - 1);
    painter.drawLine(0, height() - 1, width() - 1, 0);
}

DrawWindow::~DrawWindow()
{
}
