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


void MainWindow::on_color1_clicked()
{
    QColor color = QColorDialog().getColor();
    if (color.isValid())
    {
        ui->widget->setLineColor(color);
    }
}

void MainWindow::on_color2_clicked()
{
    QColor color = QColorDialog().getColor();
    if (color.isValid())
    {
        ui->widget->setRectColor(color);
    }
}

void MainWindow::on_color3_clicked()
{
    QColor color = QColorDialog().getColor();
    if (color.isValid())
    {
        ui->widget->setClipColor(color);
    }
}
