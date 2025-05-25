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

    // Nuppude connectimine
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::on_sortButton_clicked);

    // Andmete sisse lugemine
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
        taskList.append(task);
        ui->taskLineEdit->clear();
    }

    updateTaskListDisplay();
}

void MainWindow::on_deleteButton_clicked() {
    int row = ui->taskListWidget->currentRow();
    qDebug() << "Valitud rida:" << row;

    if (row >= 0) {
        QListWidgetItem *item = ui->taskListWidget->takeItem(row);
        delete item;
        taskList.remove(row);
    } else {
        QMessageBox::information(this, "Valimata", "Vali task mida kustutada");
    }
}

void MainWindow::on_deleteAllButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Kustuta kõik?",
                                  "Kas kustutan kõik?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->taskListWidget->clear();
        taskList.clear();

        QFile file("todolist.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Ei saanud kõike kustutada");
        }
    }
}

void MainWindow::on_saveTasksButton_clicked() {
    QString fileName = "todolist.txt";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Ei saa faili 'todolist.txt' avada.");
        return;
    }

    QTextStream out(&file);
    for (const TaskItem &task : taskList) {
        out << task.deadline.toString("dd.MM.yyyy") << ";"
        << task.title << ";"
        << (task.isDone ? "1" : "0") << "\n";
    }


    QMessageBox::StandardButton saved;
    saved = QMessageBox::question(this, "Salvesta & lahku",
                                  "Kõik salvestatud. Kas soovite rakenduse sulgeda?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (saved == QMessageBox::Yes) {
        file.close();
        QApplication::quit();
    }
    file.close();
}

void MainWindow::on_sortButton_clicked() {
    std::sort(taskList.begin(), taskList.end(), [](const TaskItem &a, const TaskItem &b) {
        return a.deadline < b.deadline;
    });

    qDebug() << "Sorteeritud taskid:";
    for (const TaskItem &item : taskList) {
        qDebug() << "Nimi:" << item.title << ", Tähtaeg:" << item.deadline.toString("dd-MM-yyyy");
    }

    updateTaskListDisplay();
}

void MainWindow::loadTasksFromFile() {
    QString fileName = "todolist.txt";

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return; // Kui faili pole, ei tee midagi
    }

    QTextStream in(&file);
    ui->taskListWidget->clear();
    taskList.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(";");

        if (parts.size() == 3) {
            QDate deadline = QDate::fromString(parts[0], "dd.MM.yyyy");
            QString title = parts[1];
            bool isDone = (parts[2] == "1");

            if (deadline.isValid()) {
                taskList.append({title, deadline, isDone});
            }
        }
    }


    file.close();
    updateTaskListDisplay();

    qDebug() << "Leitud asjad:";
    for (const TaskItem &item : taskList) {
        qDebug() << "Nimi:" << item.title << ", Tähtaeg:" << item.deadline.toString("dd-MM-yyyy");
    }
}



void MainWindow::updateTaskListDisplay() {
    ui->taskListWidget->clear();
    qDebug() << "Pärast clear(), listWidgetil on" << ui->taskListWidget->count() << "asja.";

    QDate today = QDate::currentDate();

    for (const TaskItem &task : taskList) {
        int daysLeft = today.daysTo(task.deadline);
        QString timeInfo;

        if (daysLeft > 0)
            timeInfo = QString("%1 päeva pärast").arg(daysLeft);
        else if (daysLeft == 0)
            timeInfo = "TÄNA!";
        else
            timeInfo = QString("Oled hiljaks jäänud %1 päeva").arg(-daysLeft);

        QString isDone = task.isDone ? " TEHTUD " : "";
        QString displayText = QString("Tähtaeg: %2, task: %1      %3 %4")
                                  .arg(task.title)
                                  .arg(task.deadline.toString("dd.MM.yyyy"))
                                  .arg(timeInfo)
                                  .arg(isDone);


        ui->taskListWidget->addItem(displayText);
    }
    qDebug() << "Pärast addItem()'s, listWidgetil on" << ui->taskListWidget->count() << "asja.";


    qDebug() << "Taskid listist:";
    for (const TaskItem &item : taskList) {
        qDebug() << "Nimi:" << item.title << ", Tähtaeg:" << item.deadline.toString("dd.MM.yyyy");
    }
}

void MainWindow::on_markDoneButton_clicked() {
     qDebug() << "on_markDoneButton_clicked() called";
    int row = ui->taskListWidget->currentRow();
    qDebug() << "Valitud rida:" << row;
    if (row >= 0 && row < taskList.size()) {
        taskList[row].isDone = true;
        updateTaskListDisplay();
    } else {
        QMessageBox::information(this, "Valimata", "Vali task mida tehtuks märkida");
    }
}

