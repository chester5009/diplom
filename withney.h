#ifndef WITHNEY_H
#define WITHNEY_H
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
using namespace std;


//структура студент
struct Student{
    int group;//номер группы
    float scores;//баллы студента
    float rate;//рейтинг
};

class Withney
{
private:
    vector<Student> *students=new vector<Student>;


public:
    Withney();
    void createStudents(int);//функция создания студентов
    void addStudent(Student);//добавление студента
    void clearStudents();//очистка студентов
    void showStudents();//показ студентов
    void sortStudents();//сортировка студентов по баллам
    void setRate();//функция утсановки рейтинга
    float calculateWithney(int,int,int,float);//подсчет коэффициента мана уитни
    void loadDataFromFields(vector<QStringList>);//загрузка данных с полей ввода
    void results();//подсчет и вывод окончательных результатов

    void setTable(vector<QStringList> data, int index); // установка таблицы критических значений
    void showTable(vector< vector<float> > *table); // показать таблицу критических значений
    void showTableCell(vector< vector<float> > *table,int,int); // показать ячейку таблицы критических значений

    void resetVariables();
    vector< vector<float> > *table001;
    vector< vector<float> > *table005;

};

#endif // WITHNEY_H
