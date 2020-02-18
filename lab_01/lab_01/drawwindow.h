#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <vector>
#include <QVector>

class DrawWindow : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:

    DrawWindow(QWidget *parent = 0);
    ~DrawWindow();

    void addPoint(QPoint p);
private:
    QVector<QPoint> points;
};

#endif // DRAWWINDOW_H
