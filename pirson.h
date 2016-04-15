#ifndef PIRSON_H
#define PIRSON_H

#include <iostream>
#include <vector>
#include <string.h>
#include <QTableWidget>
#include <math.h>
using namespace std;

struct Object{
    string name;
    double Fei;
    double Ft;
    double Fei_minus_Ft;
    double Fei_minus_Ft_square;
    double square_div_Ft;
    double pirs_emp;
};

class Pirson
{
private:
    vector<Object> data;
    double n;
    double k;
    double v;
public:
    Pirson();
    void setData(QTableWidget *table);

};

#endif // PIRSON_H
