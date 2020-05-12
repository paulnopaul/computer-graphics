#ifndef EDGETABLEWIDGET_H
#define EDGETABLEWIDGET_H

#include <QListWidget>

#include "polygonwidget.h"

class EdgeTableWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit EdgeTableWidget(QWidget *parent = nullptr);


public slots:
    void clearEdges();
    void addNewEdge(const QLine &);

private:
    int pointLen = 10;
    QList<QSharedPointer<QListWidgetItem>> itemList;
};

#endif // EDGETABLEWIDGET_H
