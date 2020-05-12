#include "edgetablewidget.h"
#include "polygonwidget.h"

EdgeTableWidget::EdgeTableWidget(QWidget *parent) : QListWidget(parent)
{
    this->addItem(QString("%1 %2 %3 %4").arg("X1", pointLen).arg("Y1", pointLen)
                                        .arg("X2", pointLen).arg("Y2", pointLen));
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
}

void EdgeTableWidget::clearEdges()
{
    for (QSharedPointer<QListWidgetItem> item:itemList)
    {
        this->removeItemWidget(item.get());
    }
    itemList.clear();
}

void EdgeTableWidget::addNewEdge(const QLine &edge)
{
    QSharedPointer<QListWidgetItem> newItem(
                new QListWidgetItem(
                    QString("%1 %2 %3 %4").arg(edge.x1(), pointLen).arg(edge.y1(), pointLen)
                                          .arg(edge.x2(), pointLen).arg(edge.y2(), pointLen)));
    itemList.push_back(newItem);
    this->addItem(newItem.get());
}
