#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <iostream>
#include "withney.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    vector<QStringList> getInfoFromFields(QString str1,QString str2);//Функция возвращающая список строк с данными об оценках учеников

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_action_exit_triggered();

    void on_action_input_triggered();

    void on_calculateButton_clicked();//

private:
    Ui::MainWindow *ui;
    Withney *mann=new Withney;
};

#endif // MAINWINDOW_H
