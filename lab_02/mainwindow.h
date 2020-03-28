#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>

#include "mydraw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_changeButton_clicked();

    void on_scaleRadio_clicked();

    void on_rotRadio_clicked();

    void on_moveRadio_clicked();

    void on_cancelButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
