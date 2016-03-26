#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>
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
    vector<QStringList> getFromCsv(QString path);//функция считывает файл .csv

    void fillTable(QTableWidget *table,vector<QStringList> list );
    int getTableOrientation(); //получить ориентацию таблицы 0 - вертикальная  1 - горизонтальная
    QString takeString();

private slots:


    void on_action_exit_triggered();

    void on_action_input_triggered();

    void on_calculateButton_clicked();//

    void on_action_csv_triggered();





    void on_calculateButton2_clicked();

    void on_addButton_clicked();



private:
    Ui::MainWindow *ui;
    Withney *mann=new Withney;
    QString stroka1=NULL;
    QString stroka2=NULL;
};

#endif // MAINWINDOW_H
