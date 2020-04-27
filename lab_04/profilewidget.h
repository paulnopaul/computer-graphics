#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <vector>
#include <utility>

#include "ellipse.h"
#include "circle.h"

double ProfileEllipse(Ellipse::Algo algo, double a, double b);

double ProfileCircle(Ellipse::Algo algo, double r);

QLineSeries *CreateEllipseSeries(Ellipse::Algo algo,
                            double a0, double an, double astep,
                            double b0, double bstep);

QLineSeries *CreateCircleSeries(Ellipse::Algo algo,
                            double r0, double rn, double step);

class ProfileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWidget(QWidget *parent = nullptr);
    void Profile();
private:

    QChart *createCircleLineChart();
    QChart *createEllipseLineChart();

    QLineSeries *createEllipseSeries(Ellipse::Algo algo);
    QLineSeries *createCircleSeries(Ellipse::Algo algo);

    QList<QChartView *> charts_views;

    QGridLayout *chart_layout;
};

#endif // PROFILEWIDGET_H
