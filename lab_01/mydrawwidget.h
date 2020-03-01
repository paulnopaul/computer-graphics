#ifndef MYDRAWWIDGET_H
#define MYDRAWWIDGET_H

#include <QWidget>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <QPainter>

using namespace std;

class MyDrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyDrawWidget(QWidget *parent = nullptr);

    void updateTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
    void addSolution(double x0, double y0, double r);
    void addPoint(double x, double y);
    void deletePoint(int n);
    void isComplete(bool x = false);
    void isSolved(bool x = false);

    static void drawCenterCircle(QPainter &p, double x0, double y0, double r);

private:
    void drawSolution(QPainter &p);
    void drawArea(QPainter &p);
    void paintEvent(QPaintEvent *event = nullptr);
    pair<double, double> leftPoint();
    pair<double, double> rightPoint();
    pair<double, double> downPoint();
    pair<double, double> upPoint();
    void setScale();

    vector<pair<double, double>> triangle;
    vector<pair<double, double>> dots;

    double scale;
    pair<double, double> move;
    pair<double, double> resPoint;
    double resR;

    bool complete;
    bool solved;
};

#endif // MYDRAWWIDGET_H
