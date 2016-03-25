#include "mainwindow.h"
#include "withney.h"
#include <QApplication>
#include <vector>
#include <stdlib.h>
#include <locale.h>
using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");




    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
