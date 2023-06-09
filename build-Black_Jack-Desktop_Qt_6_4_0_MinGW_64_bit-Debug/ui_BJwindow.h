/********************************************************************************
** Form generated from reading UI file 'BJwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BJWINDOW_H
#define UI_BJWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BJwindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BJwindow)
    {
        if (BJwindow->objectName().isEmpty())
            BJwindow->setObjectName("BJwindow");
        BJwindow->resize(800, 600);
        centralwidget = new QWidget(BJwindow);
        centralwidget->setObjectName("centralwidget");
        BJwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BJwindow);
        menubar->setObjectName("menubar");
        BJwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BJwindow);
        statusbar->setObjectName("statusbar");
        BJwindow->setStatusBar(statusbar);

        retranslateUi(BJwindow);

        QMetaObject::connectSlotsByName(BJwindow);
    } // setupUi

    void retranslateUi(QMainWindow *BJwindow)
    {
        BJwindow->setWindowTitle(QCoreApplication::translate("BJwindow", "BJwindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BJwindow: public Ui_BJwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BJWINDOW_H
