#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecting buttons
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);
   // connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTaskButton_clicked() {
    QString taskText = ui->taskLineEdit->text();
    QDate deadline = ui->deadlineEdit->date();
    QDate today = QDate::currentDate();

    if (!taskText.isEmpty()) {
        int daysLeft = today.daysTo(deadline);

        QString timeInfo;
        if (daysLeft > 0) {
            timeInfo = QString("%1 days left").arg(daysLeft);
        } else if (daysLeft == 0) {
            timeInfo = "Due today!";
        } else {
            timeInfo = QString("Overdue by %1 days").arg(-daysLeft);
        }


        QString taskWithDeadline = QString("%1 (Deadline: %2),      %3")
        .arg(taskText)
        .arg(deadline.toString("dd-MM-yyyy"))
        .arg(timeInfo);

        ui->taskListWidget->addItem(taskWithDeadline);
        ui->taskLineEdit->clear();
    }
}

void MainWindow::on_deleteButton_clicked() {
    int row = ui->taskListWidget->currentRow();
    if (row >= 0) {
        QListWidgetItem *item = ui->taskListWidget->takeItem(row);
        delete item;
    }
}

