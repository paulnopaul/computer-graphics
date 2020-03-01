#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>


// Расширяем класс QGraphicsView
class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

    void redraw();

private:
    QGraphicsScene      *scene;
    QGraphicsItemGroup  *group_1;

    QRectF head;

    QRectF lEye;
    QRectF rEye;

    QPolygonF nose;
    QPolygonF mouth;


    QLineF hair1;
    QLineF hair2;
    QLineF hair3;
    QLineF hair4;
    QLineF hair5;

private:

    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
};

#endif // MYGRAPHICVIEW_H
