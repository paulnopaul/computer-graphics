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

private slots:

    void on_backgroundColor_clicked();

    void on_redPick_valueChanged(int arg1);

    void on_greenPick_valueChanged(int arg1);

    void on_bluePick_valueChanged(int arg1);

    void on_blueColor_clicked();

    void on_blackColor_clicked();

    void on_circleDraw_clicked();

    void on_ellipseDraw_clicked();

    void on_circleGroupDraw_clicked();

    void on_ellipseGroupDraw_clicked();

private:

    Ui::MainWindow *ui;

    void updateColor();

    QColor figure_color;

    void AddEllipse(int x0, int y0, int a, int b);

    void AddCircle(int x0, int y0, int r);

    void AddEllipseGroup(int x0, int y0, int a, int b,
                         int astep, int bstep, int n);

    void AddCircleGroup(int x0, int y0, int r,
                        int rn, int rstep);
};

#endif // MAINWINDOW_H
