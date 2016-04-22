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
    table->setColumnCount(6);
    table->setRowCount(1);
    QTableWidgetItem *item=new QTableWidgetItem;
    item->setText("Эмп. частота");
    table->setHorizontalHeaderItem(0,item);
    label->setText("Метод Колмогорова-Смирнова");
    label->adjustSize();
}

void Kolm_smirnov::setData(QTableWidget *table)
{
    objs.clear();
    for (int i = 0; i < table->rowCount(); ++i) {
        Obj newObject{table->item(i,0)->text().toFloat(),0,0,0,0};
        objs.push_back(newObject);
    }



}

void Kolm_smirnov::calculate(QTableWidget *table)
{
    k=objs.size();
    for (int i = 0; i < objs.size(); ++i) {
        n+=objs.at(i).f;
    }
    cout<<n<<endl;
    float EF_emp=0;
    for (int i = 0; i < objs.size(); ++i) {
        objs.at(i).f_ch= objs.at(i).f/n;
        EF_emp+=objs.at(i).f/n;
        objs.at(i).f_emp=EF_emp;
        objs.at(i).f_theor=0.125*(i+1);
        objs.at(i).f_diff=objs.at(i).f_emp-objs.at(i).f_theor;

        cout<<round(objs.at(i).f*1000)/1000<<" "
           <<round(objs.at(i).f_ch*1000)/1000<<" "
          <<round(objs.at(i).f_emp*1000)/1000<<" "
          <<round(objs.at(i).f_theor*1000)/1000<<" "
         <<round(objs.at(i).f_diff*1000)/1000<<endl;

        /*table->item(i,2)->setText(QString::number(objs.at(i).f_emp));
        table->item(i,3)->setText(QString::number(objs.at(i).f_theor));
        table->item(i,4)->setText(QString::number(objs.at(i).f_diff));*/

        /*float f; // эмпирическая частота
        float f_ch;// эмпирическая частность
        float f_emp;//наклпденная эмпирическая
        float f_theor;//накопленная теор. частность
        float f_diff;//разность*/
    }


}

void Kolm_smirnov::fillTable(QTableWidget *table)
{
    cout<<"SIZE= "<<objs.size()<<endl;
    for (int i = 0; i < objs.size(); ++i) {


        /*table->item(i,0)->setText(QString::number(objs.at(i).f));
        table->item(i,1)->setText(QString::number(objs.at(i).f_ch));
        table->item(i,2)->setText(QString::number(objs.at(i).f_emp));
        table->item(i,3)->setText(QString::number(objs.at(i).f_theor));
        table->item(i,4)->setText(QString::number(objs.at(i).f_diff));*/

        /*float f; // эмпирическая частота
        float f_ch;// эмпирическая частность
        float f_emp;//наклпденная эмпирическая
        float f_theor;//накопленная теор. частность
        float f_diff;//разность*/
    }
}

Kolm_smirnov::Kolm_smirnov()
{

}
