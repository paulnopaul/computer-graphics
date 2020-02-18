#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPoint>

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

void MainWindow::on_dotButton_clicked()
{
    int x = ui->xEntry->text().toInt();
    int y = ui->yEntry->text().toInt();
    ui->drawWindow->addPoint(QPoint(x, y));
    ui->drawWindow->update();
}
