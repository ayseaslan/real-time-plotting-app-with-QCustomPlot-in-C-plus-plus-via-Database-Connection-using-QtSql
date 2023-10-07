/********************************************************************************
** Form generated from reading UI file 'databaseplot.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEPLOT_H
#define UI_DATABASEPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabasePlot
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DatabasePlot)
    {
        if (DatabasePlot->objectName().isEmpty())
            DatabasePlot->setObjectName("DatabasePlot");
        DatabasePlot->resize(800, 600);
        centralwidget = new QWidget(DatabasePlot);
        centralwidget->setObjectName("centralwidget");
        DatabasePlot->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DatabasePlot);
        menubar->setObjectName("menubar");
        DatabasePlot->setMenuBar(menubar);
        statusbar = new QStatusBar(DatabasePlot);
        statusbar->setObjectName("statusbar");
        DatabasePlot->setStatusBar(statusbar);

        retranslateUi(DatabasePlot);

        QMetaObject::connectSlotsByName(DatabasePlot);
    } // setupUi

    void retranslateUi(QMainWindow *DatabasePlot)
    {
        DatabasePlot->setWindowTitle(QCoreApplication::translate("DatabasePlot", "DatabasePlot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DatabasePlot: public Ui_DatabasePlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEPLOT_H
