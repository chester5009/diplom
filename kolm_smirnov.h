#ifndef KOLM_SMIRNOV_H
#define KOLM_SMIRNOV_H

#include <iostream>
#include <vector>
#include <string.h>
#include <QTableWidget>
#include <math.h>
#include <QLabel>
using namespace std;

struct Obj{
    float f; // эмпирическая частота
    float f_ch;// эмпирическая частность
    float f_emp;//наклпденная эмпирическая
    float f_theor;//накопленная теор. частность
    float f_diff;//разность
};

class Kolm_smirnov
{
private:
    vector <Obj> objs;
    float k;
    float n;
    float f;

    float f_ch_sum;
public:
    Kolm_smirnov();
    vector <Obj> getObjs() const;
    void setWidget(QTableWidget *table, QLabel *label);
    void setData(QTableWidget *table);
};

#endif // KOLM_SMIRNOV_H
