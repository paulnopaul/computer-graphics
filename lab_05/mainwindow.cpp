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
       ui->widget->set(color);
    }
}

void MainWindow::on_clearButton_clicked()
{
    ui->widget->clear();
}

void MainWindow::on_closeButton_clicked()
{
    ui->widget->close();
}

void MainWindow::on_hasDelay_stateChanged(int arg1)
{
    ui->widget->setDelay(arg1);
}
