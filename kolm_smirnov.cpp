#include "kolm_smirnov.h"

vector<Obj> Kolm_smirnov::getObjs() const
{
    return objs;
}

void Kolm_smirnov::setWidget(QTableWidget *table, QLabel *label)
{
    n=0;
    k=0;
    table->clear();
    table->clearContents();
    table->setColumnCount(1);
    table->setRowCount(1);
    QTableWidgetItem *item=new QTableWidgetItem;
    item->setText("Эмп. частота");
    table->setHorizontalHeaderItem(0,item);
    label->setText("Метод Колмогорова-Смирнова");
    label->adjustSize();
}

void Kolm_smirnov::setData(QTableWidget *table)
{

}

Kolm_smirnov::Kolm_smirnov()
{

}
