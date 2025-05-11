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

    if (!taskText.isEmpty()) {
        QString taskWithDeadline = QString("%1 (Deadline: %2)")
        .arg(taskText)
            .arg(deadline.toString("dd-MM-yyyy"));  // Use "MM" not "mm" for month

        ui->taskListWidget->addItem(taskWithDeadline);
        ui->taskLineEdit->clear();
    }
}

// See on hiline pähkel
void MainWindow::on_deleteButton_clicked() {
    int row = ui->taskListWidget->currentRow();
    if (row >= 0) {
        QListWidgetItem *item = ui->taskListWidget->takeItem(row);
        delete item;
    }
}

