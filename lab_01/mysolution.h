#ifndef MYSOLUTION_H
#define MYSOLUTION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

class MySolution
{
public:


    MySolution();

    void setDots(vector<pair<double, double>> _dots);
    void addDot(double x, double y);
    void deleteDot(int n);
    void setTriangle(double x1, double y1, double x2, double y2,
                     double x3, double y3);
    int solve(double &x, double &y, double &r);

    static bool checkTriangle(pair<double, double> d1,
                       pair<double, double> d2,
                       pair<double, double> d3);
    static bool dotsEqual(pair<double, double> a, pair<double, double> b);

    static double eps;
private:
    double x0, y0, r;
    vector<pair<double, double>> dots;
    vector<pair<double, double>> triangle;

    bool checkCircle(pair<double, double> d1,
                     pair<double, double> d2,
                     pair<double, double> d3);

    double myArea(pair<double, double> d1,
                  pair<double, double> d2,
                  pair<double, double> d3);

    // geometry
    double triangleArea(pair<double, double> d1,
                        pair<double, double> d2,
                        pair<double, double> d3);

    pair<double, double> triangleCenter(pair<double, double> d1,
                                        pair<double, double> d2,
                                        pair<double, double> d3);

    vector<double> touchingLineParams(pair<double, double> d1,
                                      pair<double, double> d2,
                                      pair<double, double> d3);

    void setCircleParams(pair<double, double> d1,
                         pair<double, double> d2,
                         pair<double, double> d3);

    bool isTouching(double a, double b, double c, double x0, double y0, double r);

    pair<double, double> touchingPoint(double a, double b, double c, double x0, double y0);

    static void lineCoeffs(double &a, double &b, double &c,
                           pair<double, double> d1,
                           pair<double, double> d2);

    vector<double> circleParams(pair<double, double> d1,
                                pair<double, double> d2,
                                pair<double, double> d3);

};

#endif // MYSOLUTION_H
