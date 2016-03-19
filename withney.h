#ifndef WITHNEY_H
#define WITHNEY_H
#include <iostream>
#include <vector>

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
    void addStudent(Student);
    void clearStudents();
    void showStudents();
    void sortStudents();
    void setRate();
    float calculateWithney(int,int,int,float);

};

#endif // WITHNEY_H
