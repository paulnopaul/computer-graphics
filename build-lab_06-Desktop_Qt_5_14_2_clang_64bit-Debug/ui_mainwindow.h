/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "edgetablewidget.h"
#include "polygonwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    PolygonWidget *widget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *isSpline;
    EdgeTableWidget *listWidget;
    QRadioButton *isPolygon;
    QPushButton *lineColorButton;
    QPushButton *colorButton;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *fillPoint;
    QCheckBox *hasDelay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1065, 599);
        QFont font;
        font.setPointSize(20);
        font.setUnderline(true);
        font.setStrikeOut(false);
        font.setKerning(true);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new PolygonWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 671, 531));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(690, 10, 361, 521));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        isSpline = new QRadioButton(layoutWidget);
        isSpline->setObjectName(QString::fromUtf8("isSpline"));

        gridLayout->addWidget(isSpline, 0, 1, 1, 1);

        listWidget = new EdgeTableWidget(layoutWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 6, 0, 1, 2);

        isPolygon = new QRadioButton(layoutWidget);
        isPolygon->setObjectName(QString::fromUtf8("isPolygon"));
        isPolygon->setEnabled(true);
        isPolygon->setChecked(true);

        gridLayout->addWidget(isPolygon, 0, 0, 1, 1);

        lineColorButton = new QPushButton(layoutWidget);
        lineColorButton->setObjectName(QString::fromUtf8("lineColorButton"));

        gridLayout->addWidget(lineColorButton, 3, 1, 1, 1);

        colorButton = new QPushButton(layoutWidget);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));

        gridLayout->addWidget(colorButton, 3, 0, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 8, 0, 1, 2);

        fillPoint = new QLabel(layoutWidget);
        fillPoint->setObjectName(QString::fromUtf8("fillPoint"));

        gridLayout->addWidget(fillPoint, 7, 0, 1, 2);

        hasDelay = new QCheckBox(layoutWidget);
        hasDelay->setObjectName(QString::fromUtf8("hasDelay"));

        gridLayout->addWidget(hasDelay, 5, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1065, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        isSpline->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\273\321\214\320\275\320\260\321\217 \320\272\321\200\320\270\320\262\320\260\321\217", nullptr));
        isPolygon->setText(QCoreApplication::translate("MainWindow", "\320\234\320\275\320\276\320\263\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", nullptr));
        lineColorButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202 \320\273\320\270\320\275\320\270\320\270", nullptr));
        colorButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202 \320\267\320\260\320\272\321\200\320\260\321\201\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\267\320\260\321\202\321\200\320\260\320\262\320\276\321\207\320\275\321\203\321\216 \321\202\320\276\321\207\320\272\321\203", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\263\320\276 \320\267\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217: ", nullptr));
        fillPoint->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\267\320\260\321\202\321\200\320\260\320\262\320\276\321\207\320\275\320\276\320\271 \321\202\320\276\321\207\320\272\320\270: (0, 0)", nullptr));
        hasDelay->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
