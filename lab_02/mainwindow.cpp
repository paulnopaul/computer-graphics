#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->changeStack->setCurrentIndex(0);
    ui->scaleRadio->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changeButton_clicked()
{
    if (ui->scaleRadio->isChecked())
    {
        double x0, y0, dx, dy;
        bool ok1, ok2, ok3, ok4;
        x0 = ui->scaleX0->text().toDouble(&ok1);
        y0 = ui->scaleY0->text().toDouble(&ok2);
        dx = ui->scaleDX->text().toDouble(&ok3);
        dy = ui->scaleDY->text().toDouble(&ok4);
        if (ok1 && ok2 && ok3 && ok4)
            ui->graphicsView->scale(x0, y0, dx, dy);
    }
    else if (ui->moveRadio->isChecked())
    {
        double dx, dy;
        bool ok1, ok2;
        dx = ui->moveDX->text().toDouble(&ok1);
        dy = ui->moveDY->text().toDouble(&ok2);
        if (ok1 && ok2)
            ui->graphicsView->move(dx, dy);
    }
    else if (ui->rotRadio->isChecked())
    {
        double x0, y0, angle;
        bool ok1, ok2, ok3;
        x0 = ui->rotateX0->text().toDouble(&ok1);
        y0 = ui->rotateY0->text().toDouble(&ok2);
        angle = ui->rotateAngle->text().toDouble(&ok3);
        if (ok1 && ok2 && ok3)
            ui->graphicsView->rotate(x0, y0, angle);
    }
    ui->graphicsView->update();
}

void MainWindow::on_scaleRadio_clicked()
{
    ui->changeStack->setCurrentIndex(0);
}

void MainWindow::on_rotRadio_clicked()
{
    ui->changeStack->setCurrentIndex(2);
}

void MainWindow::on_moveRadio_clicked()
{
    ui->changeStack->setCurrentIndex(1);
}

void MainWindow::on_cancelButton_clicked()
{
    ui->graphicsView->prev();
    ui->graphicsView->update();
}
