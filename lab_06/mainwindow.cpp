#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widget,        SIGNAL(newEdgeAdded(const QLine &)),
            ui->listWidget,    SLOT(addNewEdge(const QLine &)));

    connect(ui->widget,        SIGNAL(edgesCleared()),
            ui->listWidget,    SLOT(clearEdges()));

    connect(ui->widget,         SIGNAL(newFillPointCoords(QPoint)),
            this,               SLOT(updateFillPointCoords(QPoint)));

    connect(ui->widget,         SIGNAL(figureFilled()),
            this,               SLOT(figure_filled()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        drawColor = color;
        QString qss = QString("background-color: %1").arg(color.name());
        ui->colorButton->setStyleSheet(qss);
        ui->widget->setFillColor(color);
    }
}

void MainWindow::updateFillPointCoords(QPoint newPoint)
{
    ui->fillPoint->setText(QString("Координаты затравочной точки: (%1, %2)").
                           arg(newPoint.x()).arg(newPoint.y()));
}

void MainWindow::figure_filled()
{
    ui->label->setText(QString("Время последней закраски: %1 мс").arg(ui->widget->getLastDrawTime()));
}

void MainWindow::on_hasDelay_stateChanged(int arg1)
{
    ui->widget->setDelay(arg1);
}

void MainWindow::on_isPolygon_clicked()
{
    ui->widget->setPolygon(true);
}

void MainWindow::on_isSpline_clicked()
{
    ui->widget->setPolygon(false);
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->startPointEvent();
}

void MainWindow::on_lineColorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        drawColor = color;
        QString qss = QString("background-color: %1").arg(color.name());
        ui->lineColorButton->setStyleSheet(qss);
        ui->widget->setLineColor(color);
    }
}
