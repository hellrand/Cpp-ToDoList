/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *addTaskButton;
    QLineEdit *taskLineEdit;
    QListWidget *taskListWidget;
    QPushButton *deleteButton;
    QLabel *label;
    QLabel *label_2;
    QDateEdit *deadlineEdit;
    QPushButton *deleteAllButton;
    QPushButton *saveTasksButton;
    QPushButton *sortButton;
    QPushButton *markDoneButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        addTaskButton = new QPushButton(centralwidget);
        addTaskButton->setObjectName("addTaskButton");
        addTaskButton->setGeometry(QRect(410, 10, 101, 32));
        taskLineEdit = new QLineEdit(centralwidget);
        taskLineEdit->setObjectName("taskLineEdit");
        taskLineEdit->setGeometry(QRect(120, 20, 221, 21));
        taskListWidget = new QListWidget(centralwidget);
        taskListWidget->setObjectName("taskListWidget");
        taskListWidget->setGeometry(QRect(20, 140, 601, 191));
        taskListWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        taskListWidget->setSortingEnabled(false);
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(520, 10, 101, 32));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 81, 19));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 50, 56, 19));
        deadlineEdit = new QDateEdit(centralwidget);
        deadlineEdit->setObjectName("deadlineEdit");
        deadlineEdit->setGeometry(QRect(120, 50, 221, 25));
        deadlineEdit->setCalendarPopup(true);
        deadlineEdit->setDate(QDate(2025, 5, 1));
        deleteAllButton = new QPushButton(centralwidget);
        deleteAllButton->setObjectName("deleteAllButton");
        deleteAllButton->setGeometry(QRect(520, 360, 101, 32));
        saveTasksButton = new QPushButton(centralwidget);
        saveTasksButton->setObjectName("saveTasksButton");
        saveTasksButton->setGeometry(QRect(400, 360, 101, 32));
        sortButton = new QPushButton(centralwidget);
        sortButton->setObjectName("sortButton");
        sortButton->setGeometry(QRect(270, 360, 111, 32));
        markDoneButton = new QPushButton(centralwidget);
        markDoneButton->setObjectName("markDoneButton");
        markDoneButton->setGeometry(QRect(520, 100, 101, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addTaskButton->setText(QCoreApplication::translate("MainWindow", "Add task", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Task name:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Deadline:", nullptr));
        deadlineEdit->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd.MM.yyyy", nullptr));
        deleteAllButton->setText(QCoreApplication::translate("MainWindow", "Delete all", nullptr));
        saveTasksButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        sortButton->setText(QCoreApplication::translate("MainWindow", "Sort by deadline", nullptr));
        markDoneButton->setText(QCoreApplication::translate("MainWindow", "Task Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
