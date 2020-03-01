#ifndef MYDOTTABLE_H
#define MYDOTTABLE_H

#include <QTableView>
#include <QtGui>
#include <QWidget>

class MyDotTable : public QTableView
{
Q_OBJECT
public:
    MyDotTable();
    MyDotTable(QWidget *parent);
};

#endif // MYDOTTABLE_H
