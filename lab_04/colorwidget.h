#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QPainter>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = nullptr);
    void Update(QColor color);
private:
    void paintEvent(QPaintEvent *event = nullptr) override;
    QColor color;
};

#endif // COLORWIDGET_H
