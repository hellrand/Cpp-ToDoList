#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <algorithm>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->deadlineEdit->setDate(QDate::currentDate());

    // Connecting buttons
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::on_sortButton_clicked);
    //connect(ui->markDoneButton, &QPushButton::clicked, this, &MainWindow::on_markDoneButton_clicked);



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

    if (!taskText.isEmpty()) {
        TaskItem task{taskText, deadline};
        taskList.append(task);  // ✅ only modify the vector
        ui->taskLineEdit->clear();
    }
    updateTaskListDisplay();  // ✅ rebuild the entire list from the sorted/updated vector
}

void MainWindow::on_deleteButton_clicked() {
    int row = ui->taskListWidget->currentRow();
    qDebug() << "Selected row:" << row;  // ← should NOT be -1

    if (row >= 0) {
        QListWidgetItem *item = ui->taskListWidget->takeItem(row);
        delete item;
        taskList.remove(row);
    }
}

void MainWindow::on_deleteAllButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete All",
                                  "Are you sure you want to delete all tasks?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->taskListWidget->clear();
        taskList.clear();

        QFile file("todolist.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            file.close();  // writing nothing truncates it
        } else {
            QMessageBox::warning(this, "Error", "Could not clear 'todolist.txt'");
        }
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

    QMessageBox::StandardButton saved;
    saved = QMessageBox::question(this, "Save & Exit",
                                  "All tasks have been saved. Do you want to exit?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (saved == QMessageBox::Yes) {
        file.close();
        QApplication::quit();
    }
    file.close();

    //QMessageBox::information(this, "Saved", "All tasks saved to 'todolist.txt'.");
}

void MainWindow::on_sortButton_clicked() {
    std::sort(taskList.begin(), taskList.end(), [](const TaskItem &a, const TaskItem &b) {
        return a.deadline < b.deadline;
    });

    qDebug() << "Sorted tasks:";
    for (const TaskItem &item : taskList) {
        qDebug() << "Text:" << item.title << ", Deadline:" << item.deadline.toString("dd-MM-yyyy");
    }

    updateTaskListDisplay(); // Refresh UI after sort
}

void MainWindow::loadTasksFromFile() {
    QString fileName = "todolist.txt";

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return; // Do nothing if the file doesn't exist
    }

    QTextStream in(&file);
    ui->taskListWidget->clear();  // Clear current tasks
    taskList.clear();             // Clear internal task list

    QRegularExpression re(R"(Deadline:\s*(\d{2}\.\d{2}\.\d{4}),\s*task:\s*(.+?)\s+(?:Due today!|\d+\s+days\s+left))");

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        qDebug() << "Read line:" << line;

        QRegularExpressionMatch match = re.match(line);
        if (match.hasMatch()) {
            QString dateStr = match.captured(1);  // e.g. 29.05.2025
            QString taskTitle = match.captured(2);  // e.g. aamm

            QDate deadline = QDate::fromString(dateStr, "dd.MM.yyyy");
            if (deadline.isValid()) {
                taskList.append({taskTitle, deadline});
            }
        }
    }

    file.close();
    updateTaskListDisplay();

    qDebug() << "Loaded tasks:";
    for (const TaskItem &item : taskList) {
        qDebug() << "Text:" << item.title << ", Deadline:" << item.deadline.toString("dd-MM-yyyy");
    }
}



void MainWindow::updateTaskListDisplay() {
    ui->taskListWidget->clear();
    qDebug() << "After clear(), listWidget has" << ui->taskListWidget->count() << "items.";

    QDate today = QDate::currentDate();

    for (const TaskItem &task : taskList) {
        int daysLeft = today.daysTo(task.deadline);
        QString timeInfo;

        if (daysLeft > 0)
            timeInfo = QString("%1 days left").arg(daysLeft);
        else if (daysLeft == 0)
            timeInfo = "Due today!";
        else
            timeInfo = QString("Overdue by %1 days").arg(-daysLeft);

        QString isDone = task.isDone ? " DONE " : "";
        QString displayText = QString("Deadline: %2, task: %1      %3 %4")
                                  .arg(task.title)
                                  .arg(task.deadline.toString("dd.MM.yyyy"))
                                  .arg(timeInfo)
                                  .arg(isDone);


        ui->taskListWidget->addItem(displayText);
    }
    qDebug() << "After addItem()'s, listWidget has" << ui->taskListWidget->count() << "items.";


    qDebug() << "Tasks now in List:";
    for (const TaskItem &item : taskList) {
        qDebug() << "Text:" << item.title << ", Deadline:" << item.deadline.toString("dd.MM.yyyy");
    }
}

void MainWindow::on_markDoneButton_clicked() {
     qDebug() << "on_markDoneButton_clicked() called";
    int row = ui->taskListWidget->currentRow();
    qDebug() << "Selected row:" << row;  // ← should NOT be -1
    if (row >= 0 && row < taskList.size()) {
        taskList[row].isDone = true;
        updateTaskListDisplay();
    } else {
        QMessageBox::information(this, "No Selection", "Please select a task to mark as done.");
    }
}

