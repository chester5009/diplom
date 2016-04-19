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
};

class Pirson
{
private:
    float *pirson_t1;
    float *pirson_t2;
    void initTables();
    vector<Object> data;
    double n;
    double k;
    double v;
    double pirs_emp;
public:
    Pirson();
    void setData(QTableWidget *table);
    void showData();

};

#endif // PIRSON_H
