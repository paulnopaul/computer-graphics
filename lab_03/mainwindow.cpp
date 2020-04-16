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

QColor getColor(QString colorName)
{
    QColor color = Qt::transparent;
    if (colorName== "Синий")
        color = Qt::blue;
    else if (colorName == "Черный")
        color = Qt::black;
    else if (colorName== "Красный")
        color = Qt::red;
    else if (colorName == "Зеленый")
        color = Qt::green;
    else if (colorName == "Желтый")
        color = Qt::yellow;
    else if (colorName == "Фоновый")
        color = Qt::white;
    return color;
}

AlgoType getType(QString typeName)
{
    AlgoType type = AlgoType::DEFAULT;
    if (typeName== "ЦДА")
        type = AlgoType::DDA;
    else if (typeName == "Брезенхем int")
        type = AlgoType::INT_BRESENHAM;
    else if (typeName == "Брезенхем float")
        type = AlgoType::FLOAT_BRESENHAM;
    else if (typeName == "Брезенхем с устранением ступенчатости")
        type = AlgoType::SMOOTH_BRESENHAM;
    else if (typeName == "Ву")
        type = AlgoType::WU;
    else if (typeName == "Библиотечный")
        type = AlgoType::LIBRARY;
    return type;
}

void MainWindow::on_pushButton_clicked()
{
    QPoint start, end;
    bool ok = true;
    start.setX(ui->x1Entry->text().toInt(&ok));
    if (ok)
        end.setX(ui->x2Entry->text().toInt(&ok));
    if (ok)
        start.setY(ui->y1Entry->text().toInt(&ok));
    if (ok)
        end.setY(ui->y2Entry->text().toInt(&ok));

    QColor color = getColor(ui->colorChoose->currentText());
    AlgoType type = getType(ui->algorythmChoose->currentText());


    if (ok)
        ui->singleLineDraw->drawLine(start, end, type, color);
}

void MainWindow::on_visualDrawButton_clicked()
{
    bool ok;
    const double pi = 3.14159265359f;
    double step = ui->degreeStepEntry->text().toDouble(&ok);
    step = step * pi / 180;

    QColor color = getColor(ui->visualColorChoose->currentText());
    AlgoType type = getType(ui->visualAlgorithmChoose->currentText());

    if (ok)
        ui->visualLineDraw->drawDifferentLines(step, type, color);

}

void MainWindow::on_visualCleanButton_clicked()
{
    ui->visualLineDraw->clear();
}

void MainWindow::on_cleanButton_clicked()
{
    ui->singleLineDraw->clear();
}
