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

    void on_colorButton_clicked();

    void on_clearButton_clicked();

    void on_closeButton_clicked();

    void on_fillButton_clicked();

    void on_hasDelay_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QColor drawColor = Qt::black;
};
#endif // MAINWINDOW_H
