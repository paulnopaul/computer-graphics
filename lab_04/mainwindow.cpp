#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ellipse::Algo TypeFromName(const QString &name)
{
    if (name == "Каноническое уравнение")
        return Ellipse::Algo::CANONICAL;
    else if (name == "Параметрическое уравнение")
        return Ellipse::Algo::PARAMETRIC;
    else if (name == "Параметрическое уравнение")
        return Ellipse::Algo::BRESENHAM;
    else if (name == "Параметрическое уравнение")
        return Ellipse::Algo::MIDPOINT;
    else
        return Ellipse::Algo::LIBRARY;
}

void MainWindow::on_redPick_valueChanged(int arg1)
{
    this->updateColor();
}

void MainWindow::on_greenPick_valueChanged(int arg1)
{
    this->updateColor();
}

void MainWindow::on_bluePick_valueChanged(int arg1)
{
    this->updateColor();
}

void MainWindow::updateColor()
{
    int r = ui->redPick->value();
    int g = ui->greenPick->value();
    int b = ui->bluePick->value();
    figure_color.setRgb(r, g, b);
    ui->colorView->Update(figure_color);
}

void MainWindow::on_backgroundColor_clicked()
{
    ui->redPick->setValue(255);
    ui->greenPick->setValue(255);
    ui->bluePick->setValue(255);
}

void MainWindow::on_blueColor_clicked()
{
    ui->redPick->setValue(0);
    ui->greenPick->setValue(0);
    ui->bluePick->setValue(255);
}

void MainWindow::on_blackColor_clicked()
{
    ui->redPick->setValue(0);
    ui->greenPick->setValue(0);
    ui->bluePick->setValue(0);
}

void MainWindow::AddCircle(int x0, int y0, int r)
{
    ui->drawer->AddEllipse(Circle(TypeFromName(ui->algoPick->currentText()),
                                  x0, y0, r), this->figure_color);
}

void MainWindow::AddEllipse(int x0, int y0, int a, int b)
{
    ui->drawer->AddEllipse(Ellipse(TypeFromName(ui->algoPick->currentText()),
                                   x0, y0, a, b), this->figure_color);
}

void MainWindow::AddEllipseGroup(int x0, int y0, int a, int b, int astep, int bstep, int n)
{
    for (int i = 0; i < n; ++i, a += astep, b += bstep)
        AddEllipse(x0, y0, a, b);
}

void MainWindow::AddCircleGroup(int x0, int y0, int r, int rn, int rstep)
{
    if (rstep != 0)
    {
        int count = (rn - r) / rstep;
        rstep *= (count > 0 ? 1 : -1);
        count = abs(count) + 1;
        for (int i = 1; i < count; ++i, r += rstep)
            AddCircle(x0, y0, r);
    }
}

void MainWindow::on_circleDraw_clicked()
{
    int x0, y0, r;
    bool ok;
    x0 = ui->circleX0->text().toInt(&ok);
    if (ok)
        y0 = ui->circleY0->text().toInt(&ok);
    if (ok)
        r = ui->circleR->text().toInt(&ok);
    if (ok)
        AddCircle(x0, y0, r);
}

void MainWindow::on_ellipseDraw_clicked()
{
    int x0, y0, a, b;
    bool ok;
    x0 = ui->ellipseX0->text().toInt(&ok);
    if (ok)
        y0 = ui->ellipseY0->text().toInt(&ok);
    if (ok)
        a = ui->ellipseA->text().toInt(&ok);
    if (ok)
        b = ui->ellipseB->text().toInt(&ok);
    if (ok)
        AddEllipse(x0, y0, a, b);
}

void MainWindow::on_circleGroupDraw_clicked()
{
    int x0, y0, r, rn, rstep;
    bool ok;
    x0 = ui->circleX0->text().toInt(&ok);
    if (ok)
        y0 = ui->circleY0->text().toInt(&ok);
    if (ok)
        r = ui->circleR->text().toInt(&ok);
    if (ok)
        rn = ui->circleGroupRN->text().toInt(&ok);
    if (ok)
        rstep = ui->circleGroupStep->text().toInt(&ok);
    if (ok)
        AddCircleGroup(x0, y0, r, rn, rstep);
}

void MainWindow::on_ellipseGroupDraw_clicked()
{
    int x0, y0, a, b, astep, bstep, n;
    bool ok;
    x0 = ui->ellipseX0->text().toInt(&ok);
    if (ok)
        y0 = ui->ellipseY0->text().toInt(&ok);
    if (ok)
        a = ui->ellipseA->text().toInt(&ok);
    if (ok)
        b = ui->ellipseB->text().toInt(&ok);
    if (ok)
        astep = ui->ellipseGroupAStep->text().toInt(&ok);
    if (ok)
        bstep = ui->ellipseGroupBStep->text().toInt(&ok);
    if (ok)
        n = ui->ellipseGroupN->text().toInt(&ok);
    if (ok)
        AddEllipseGroup(x0, y0, a, b, astep, bstep, n);
}
