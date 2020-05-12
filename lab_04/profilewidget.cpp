#include "profilewidget.h"


#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

double ProfileEllipse(Ellipse::Algo algo, double a, double b)
{
    steady_clock::time_point start(steady_clock::now());
    Ellipse e(algo, 0, 0, a, b);
    steady_clock::time_point finish(steady_clock::now());
    auto dur = finish - start;
    return duration_cast<milliseconds>(dur).count();
}

double ProfileCircle(Ellipse::Algo algo, double r)
{
    steady_clock::time_point start(steady_clock::now());
    Circle c(algo, 0, 0, r);
    steady_clock::time_point finish(steady_clock::now());
    auto dur = finish - start;
    return duration_cast<milliseconds>(dur).count();
}

QLineSeries *CreateEllipseSeries(Ellipse::Algo algo,
                            double a0, double an, double astep,
                            double b0, double bstep)
{
    QLineSeries *profile_stats = new QLineSeries;
    if (algo == Ellipse::Algo::BRESENHAM)
        profile_stats->setName("Брезенхем");
    else if (algo == Ellipse::Algo::CANONICAL)
        profile_stats->setName("Канон");
    else if (algo == Ellipse::Algo::PARAMETRIC)
        profile_stats->setName("Парам");
    else if (algo == Ellipse::Algo::MIDPOINT)
        profile_stats->setName("Средняя точка");

    for (double a = a0, b = b0; a <= an; a += astep, b += bstep)
        profile_stats->append(a, ProfileEllipse(algo, a, b));

    profile_stats->setPointsVisible(false);

    return profile_stats;
}

QLineSeries *CreateCircleSeries(Ellipse::Algo algo,
                            double r0, double rn, double step)
{
    QLineSeries *profile_stats = new QLineSeries;

    if (algo == Ellipse::Algo::BRESENHAM)
        profile_stats->setName("Брезенхем");
    else if (algo == Ellipse::Algo::CANONICAL)
        profile_stats->setName("Канон");
    else if (algo == Ellipse::Algo::PARAMETRIC)
        profile_stats->setName("Парам");
    else if (algo == Ellipse::Algo::MIDPOINT)
        profile_stats->setName("Средняя точка");

    for (double r = r0; r <= rn; r += step)
        profile_stats->append(r, ProfileCircle(algo, r));

    profile_stats->setPointsVisible(false);

    return profile_stats;
}

QLineSeries *ProfileWidget::createEllipseSeries(Ellipse::Algo algo)
{
    double a0 =     2; // 1'000;
    double an =     170002; // 100'000;
    double astep =  10000; // 1'000;
    double b0 =     2; // 1'000;
    double bstep =  10000;

    return CreateEllipseSeries(algo, a0, an, astep, b0, bstep);
}


QLineSeries *ProfileWidget::createCircleSeries(Ellipse::Algo algo)
{
    double r0 =     2; // 1'000;
    double rn =     170002; // 100'000;
    double step =   10000; // 1'000;

    return CreateCircleSeries(algo, r0, rn, step);
}


QChart *ProfileWidget::createCircleLineChart()
{
    QChart *chart = new QChart;
    chart->setTitle("Алгоритмы построения окружностей");

    QList<QLineSeries *> series;
    series << createCircleSeries(Ellipse::Algo::CANONICAL);
    series << createCircleSeries(Ellipse::Algo::PARAMETRIC);
    series << createCircleSeries(Ellipse::Algo::BRESENHAM);
    series << createCircleSeries(Ellipse::Algo::MIDPOINT);

    for (QLineSeries * s: series)
        chart->addSeries(s);

    chart->createDefaultAxes();
    chart->localizeNumbers();

    return chart;
}

QChart *ProfileWidget::createEllipseLineChart()
{
    QChart *chart = new QChart;
    chart->setTitle("Алгоритмы построения эллипсов");

    QList<QLineSeries *> series;
    series << createEllipseSeries(Ellipse::Algo::CANONICAL);
    series << createEllipseSeries(Ellipse::Algo::PARAMETRIC);
    series << createEllipseSeries(Ellipse::Algo::BRESENHAM);
    series << createEllipseSeries(Ellipse::Algo::MIDPOINT);

    for (QLineSeries * s: series)
        chart->addSeries(s);

    chart->createDefaultAxes();

    return chart;
}


void ProfileWidget::Profile()
{
    this->update();
}

ProfileWidget::ProfileWidget(QWidget *parent) : QWidget(parent)
{
    chart_layout = new QGridLayout();
    QChartView *chart_view;

    chart_view = new QChartView(createCircleLineChart());
    this->chart_layout->addWidget(chart_view);
    charts_views << chart_view;

    chart_view = new QChartView(createEllipseLineChart());
    this->chart_layout->addWidget(chart_view);
    charts_views << chart_view;

    this->setLayout(chart_layout);
}
