#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <mygraphicsview.h>
#include <QKeyEvent>
#include "mysolution.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_solveButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow  *ui;
    int dotNumber;
    MySolution solution;
};

#endif // MAINWINDOW_H
