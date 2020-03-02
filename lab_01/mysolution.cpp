#include "mysolution.h"

MySolution::MySolution()
{
}

double MySolution::eps = 1e-8;

void MySolution::setDots(vector<pair<double, double>> _dots)
{
    this->dots = _dots;
}

void MySolution::addDot(double x, double y)
{
    this->dots.push_back({x, y});
}

bool MySolution::checkTriangle(pair<double, double> d1, pair<double, double> d2, pair<double, double> d3)
{
    if (!dotsEqual(d1, d2) && !dotsEqual(d2, d3) && !dotsEqual(d1, d3))
        return true;
    return false;
}

bool MySolution::dotsEqual(pair<double, double> a, pair<double, double> b)
{
    if (fabs(a.first - b.first) < MySolution::eps &&
        fabs(a.second - b.second) < MySolution::eps)
        return true;
    return false;
}

void MySolution::deleteDot(int n)
{
    if (n < (int)this->dots.size())
        this->dots.erase(this->dots.begin() + n);
}

void MySolution::setTriangle(double x1, double y1, double x2, double y2,
                 double x3, double y3)
{
    this->triangle = vector<pair<double, double>>({{x1, y1}, {x2, y2}, {x3, y3}});
}

int MySolution::solve(double &_x, double &_y, double &_r, double &_tx, double &_ty)
{

    // for (const pair<double, double> &d: this->dots)
    //     cout << d.first << " " << d.second << " " << endl;


    double max_area = -1, area;
    for (pair<double, double> dot1 : this->dots)
        for (pair<double, double> dot2 : this->dots)
            for (pair<double, double> dot3 : this->dots)
            {
                if (dot1 != dot2 && dot1 != dot3 && dot2 != dot3)
                    if (this->checkCircle(dot1, dot2, dot3) &&
                            (area = myArea(dot1, dot2, dot3)) > max_area)
                    {
                            max_area = area;
                            setCircleParams(dot1, dot2, dot3);
                    }
                /*
                cout << dot1.first << " " << dot1.second <<
                        dot2.first << " " << dot2.second <<
                        dot3.first << " " << dot3.second << endl;*/
            }
    if (max_area != -1)
    {
        _x = this->x0;
        _y = this->y0;
        _r = this->r;
        _tx = this->tx;
        _ty = this->ty;
        return 0;
    }
    return 1;
}

double MySolution::myArea(pair<double, double> d1,
               pair<double, double> d2,
               pair<double, double> d3)
{
    pair<double, double> tCenter = this->triangleCenter(this->triangle[0], this->triangle[1],
            this->triangle[2]);
    vector<double> circle =  this->circleParams(d1, d2, d3);
    pair<double, double> cCenter = pair<double, double>(circle[0], circle[1]);
    vector<double> tLineParams = this->touchingLineParams(d1, d2, d3);
    pair<double, double> tPoint = this->touchingPoint(tLineParams[0], tLineParams[1], tLineParams[2],
            circle[0], circle[1]);
    return triangleArea(tCenter, cCenter, tPoint);
}

bool MySolution::checkCircle(pair<double, double> d1,
                             pair<double, double> d2,
                             pair<double, double> d3)
{
    // cout << d1.first << " " << d1.second << " " <<
    //         d2.first << " " << d2.second << " " <<
    //         d3.first << " " << d3.second << endl;
    vector<double> circle =  this->circleParams(d1, d2, d3);
    double x0 = circle[0], y0 = circle[1], r = circle[2];
    double aL, bL, cL;

    this->lineCoeffs(aL, bL, cL, this->triangle[0], this->triangle[1]);
    if (this->isTouching(aL, bL, cL, x0, y0, r))
        return true;
    // cout << aL << " " << bL << " " << cL << endl;
    this->lineCoeffs(aL, bL, cL, this->triangle[1], this->triangle[2]);
    if (this->isTouching(aL, bL, cL, x0, y0, r))
        return true;
    // cout << aL << " " << bL << " " << cL << endl;
    this->lineCoeffs(aL, bL, cL, this->triangle[0], this->triangle[2]);
    if (this->isTouching(aL, bL, cL, x0, y0, r))
        return true;
    // cout << aL << " " << bL << " " << cL << endl;
    return false;
}

vector<double> MySolution::touchingLineParams(pair<double, double> d1,
                                 pair<double, double> d2,
                                 pair<double, double> d3)
{
    vector<double> circle =  this->circleParams(d1, d2, d3);
    double x0 = circle[0], y0 = circle[1], r = circle[2];
    double aL, bL, cL;

    this->lineCoeffs(aL, bL, cL, this->triangle[0], this->triangle[1]);
    if (this->isTouching(aL, bL, cL, x0, y0, r))
        return {aL, bL, cL};

    this->lineCoeffs(aL, bL, cL, this->triangle[1], this->triangle[2]);
    if (this->isTouching(aL, bL, cL, x0, y0, r))
        return {aL, bL, cL};

    this->lineCoeffs(aL, bL, cL, this->triangle[0], this->triangle[2]);
    if (this->isTouching(aL, bL, cL, x0, y0, r))
        return {aL, bL, cL};

    return {0, 0, 0};
}


double MySolution::triangleArea(pair<double, double> d1,
                     pair<double, double> d2,
                     pair<double, double> d3)
{
    double area = 0;
    area = (d1.first - d3.first) * (d2.second - d3.second) -
            (d2.first - d3.first) * (d1.second - d3.second);
    area = fabs(area / 2);
    return area;
}

bool MySolution::isTouching(double a, double b, double c, double x0, double y0, double r)
{
    double dSq, aSq, bSq, cSq;
    if (fabs(a) > this->eps)
    {
        aSq = ((b * b) / (a * a)) + 1;
        bSq = 2 * b * c / (a * a) + 2 * (b / a) * x0 - 2 * y0;
        cSq = 2 * x0 * c / a + (c * c) / (a * a) + y0 * y0 + x0 * x0 + r * r;
    }
    else
    {
        aSq = 1;
        bSq = 2 * x0;
        cSq = x0 * x0 + y0 * y0 + (c * c) / (b * b) + 2 * y0 * c / b - r * r;
    }
    dSq = bSq * bSq - 4 * aSq * cSq;
    if (fabs(dSq) < this->eps)
        return true;
    return false;
}

void MySolution::lineCoeffs(double &a, double &b, double &c,
                       pair<double, double> d1,
                       pair<double, double> d2)
{
    a = d1.second - d2.second;
    b = d2.first - d1.first;
    c = d1.first * d2.second - d2.first * d1.second;
}

vector<double> MySolution::circleParams(pair<double, double> d1,
                     pair<double, double> d2,
                     pair<double, double> d3)
{
    vector<double> circle(3);
    double z1 = d1.first * d1.first + d1.second * d1.second;
    double z2 = d2.first * d2.first + d2.second * d2.second;
    double z3 = d3.first * d3.first + d3.second * d3.second;

    double x12 = d1.first - d2.first;
    double x23 = d2.first - d3.first;
    double x31 = d3.first - d1.first;

    double y12 = d1.second - d2.second;
    double y23 = d2.second - d3.second;
    double y31 = d3.second - d1.second;

    double z = x12 * y31 - y12 * x31;
    double zx = y12 * z3 + y23 * z1 + y31 * z2;
    double zy = x12 * z3 + x23 * z1 + x31 * z2;

    circle[0] = -zx / (2 * z);
    circle[1] = zy / (2 * z);
    circle[2] = sqrt((d1.first - circle[0]) * (d1.first - circle[0]) +
            (d1.second - circle[1]) * (d1.second - circle[1]));
    return circle;
}

pair<double, double> MySolution::touchingPoint(double a, double b, double c, double x0, double y0)
{
    double aSq, bSq;
    pair<double, double> point;
    cout << a << " " << b << " " << c << endl;
    if (fabs(a) > eps)
    {
        cout << "HELLLO\n";
        aSq = ((b * b) / (a * a)) + 1;
        bSq = 2 * b * c / (a * a) + 2 * (b / a) * x0 - 2 * y0;
        point.second = (-b / a) * point.second - c / a;
    }
    else
    {
        cout << "HELLLLLLOOOOOOOOOO\n";
        aSq = 1;
        bSq = -2 * x0;
        point.second = -c / b;
    }
    point.first = -bSq / (2 * aSq);
    cur_tx = point.first;
    cur_ty = point.second;
    return point;
}

void MySolution::setCircleParams(pair<double, double> d1,
                      pair<double, double> d2,
                      pair<double, double> d3)
{
    vector<double> circle = circleParams(d1, d2, d3);
    this->x0 = circle[0];
    this->y0 = circle[1];
    this->r = circle[2];
    this->tx = cur_tx;
    this->ty = cur_ty;
}

pair<double, double> MySolution::triangleCenter(pair<double, double> d1,
                                     pair<double, double> d2,
                                     pair<double, double> d3)
{
    pair<double, double> dot;
    dot.first = (d1.first + d2.first + d3.first) / 3;
    dot.second = (d1.second + d2.second + d3.second) / 3;
    return dot;
}
