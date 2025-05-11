#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->deadlineEdit->setDate(QDate::currentDate());

    // Connecting buttons
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);


    // Loads all tasks from file on start
    loadTasksFromFile();

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
        .arg(deadline.toString("dd.MM.yyyy"))
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

void MainWindow::on_deleteAllButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete All",
                                  "Are you sure you want to delete all tasks?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->taskListWidget->clear();
    }
}

void MainWindow::on_saveTasksButton_clicked() {
    QString fileName = "todolist.txt";  // Save to fixed file name

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open 'todolist.txt' for writing.");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < ui->taskListWidget->count(); ++i) {
        QListWidgetItem *item = ui->taskListWidget->item(i);
        out << item->text() << "\n";
    }

    file.close();
    QMessageBox::information(this, "Saved", "All tasks saved to 'todolist.txt'.");
}

void MainWindow::loadTasksFromFile() {
    QString fileName = "todolist.txt";

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Optional: show a warning only if the file is expected to exist
        return; // Do nothing if the file doesn't exist
    }

    QTextStream in(&file);
    ui->taskListWidget->clear();  // Clear current tasks

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.trimmed().isEmpty()) {
            ui->taskListWidget->addItem(line);
        }
    }

    file.close();
}

