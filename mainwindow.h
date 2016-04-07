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
#include <QMessageBox>
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



    void on_buttonBox_accepted();

    void on_action_help_triggered();

    //void on_table_input_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_table_input_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Withney *mann=new Withney;
    QString stroka1=NULL;
    QString stroka2=NULL;
    int method; //0-mann 1-kolmogorov
};

#endif // MAINWINDOW_H
