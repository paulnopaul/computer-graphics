#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:

private slots:

    void figure_filled();

    void updateFillPointCoords(QPoint newPoint);

    void on_colorButton_clicked();

    void on_hasDelay_stateChanged(int arg1);

    void on_isPolygon_clicked();

    void on_isSpline_clicked();

    void on_pushButton_clicked();

    void on_lineColorButton_clicked();

private:
    Ui::MainWindow *ui;
    QColor drawColor = Qt::black;
};
#endif // MAINWINDOW_H
