#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

class DrawWindow : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:

    DrawWindow(QWidget *parent = 0);
    ~DrawWindow();

};

#endif // DRAWWINDOW_H
