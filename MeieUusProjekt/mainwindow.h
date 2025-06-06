#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QVector>

struct TaskItem {
    QString title;
    QDate deadline;
    bool isDone = false;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadTasksFromFile();


private slots:
    void on_addTaskButton_clicked();
    void on_deleteButton_clicked();
    void on_deleteAllButton_clicked();
    void on_saveTasksButton_clicked();
    void on_sortButton_clicked();
    void on_markDoneButton_clicked();


private:
    Ui::MainWindow *ui;
    void updateTaskListDisplay();
    QVector<TaskItem> taskList;
};
#endif // MAINWINDOW_H
