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
#include "pirson.h"
#include "kolm_smirnov.h"
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

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
    vector<QStringList> getInfoFromFields2(QString str1);//Функция возвращающая список строк с данными об оценках учеников
    vector<QStringList> getFromCsv(QString path);//функция считывает файл .csv

    void fillTable(QTableWidget *table,vector<QStringList> list );
    int getTableOrientation(); //получить ориентацию таблицы 0 - вертикальная  1 - горизонтальная
    QString takeString(QTableWidget *table);

    vector<QStringList> getDataFromTable(QTableWidget *table, int groupCount);

    void outputTable(vector<Student> *students,QTableWidget *table);

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

    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

    void on_buttonChangeName_clicked();

    void on_textEdit_3_textChanged();

    void on_textEdit_4_textChanged();

    void on_button_calc_clicked();

    void on_button_Mann_clicked();

    void on_button_Pirson_clicked();

    void on_button_pirson_addrow_clicked();

    void on_button_pirson_deleterow_clicked();

    void on_button_pirson_calc_clicked();

    void on_button_K_S_clicked();

private:
    Ui::MainWindow *ui;
    Withney *mann=new Withney;
    Pirson *pirson=new Pirson;
    Kolm_smirnov *smirnov=new Kolm_smirnov;
    QString stroka1=NULL;
    QString stroka2=NULL;
    int method; //0-mann 1- pirson 2-kolmogorov
    int howInput;//0-общий список ,1- по 2 группы
    void deleteIndeces(QModelIndexList *m);
    void sortIndeces(QModelIndexList *m);
    void tableCorrector(QTableWidget *table);
    QString nameGroup1="Контрольная";
    QString nameGroup2="Экспериментальная";

    QGraphicsScene *scene;
    QLine *line1;
};

#endif // MAINWINDOW_H
