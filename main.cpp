#include "mainwindow.h"
#include "withney.h"
#include <QApplication>
#include <vector>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    Withney *mann=new Withney;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    mann->createStudents(11);
    mann->showStudents();
    mann->sortStudents();
    mann->showStudents();
    mann->setRate();
    mann->showStudents();

    return a.exec();
}
