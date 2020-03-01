#ifndef MYDRAWWIDGET_H
#define MYDRAWWIDGET_H

#include <QWidget>
#include <vector>
#include <algorithm>
#include <QPainter>

using namespace std;

class MyDrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyDrawWidget(QWidget *parent = nullptr);

    void updateTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
    void addPoint(double x, double y);
    void deletePoint(int n);
    void isComplete(bool x = false);
    void isSolved(bool x = false);

    void drawSolution(QPainter &p);
    void drawArea(QPainter &p);
    void paintEvent(QPaintEvent *event = nullptr);
private:
    vector<pair<double, double>> triangle;
    vector<pair<double, double>> dots;
    double scale;
    bool complete;
    bool solved;
};

#endif // MYDRAWWIDGET_H
