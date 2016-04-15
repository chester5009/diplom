#include "pirson.h"

Pirson::Pirson()
{

}

void Pirson::setData(QTableWidget *table)
{
    pirs_emp=0;
    n=0;
    k=0;
    k=table->rowCount();
    for (int i = 0; i < k; ++i) {
        Object newObject{};
        newObject.name=table->item(i,0)->text().toUtf8().constData();
        newObject.Fei=table->item(i,1)->text().toDouble();
        data.push_back(newObject);
        n+=table->item(i,1)->text().toDouble();

    }
    for (int j = 0; j < data.size(); ++j) {
        data.at(j).Ft=n/k;
        data.at(j).Fei_minus_Ft=data.at(j).Fei-data.at(j).Ft;
        data.at(j).Fei_minus_Ft_square=pow(data.at(j).Fei_minus_Ft,2);
        data.at(j).square_div_Ft=data.at(j).Fei_minus_Ft_square / data.at(j).Ft;
        pirs_emp+=data.at(j).square_div_Ft;
    }

}

void Pirson::showData()
{
    for (int i = 0; i < data.size(); ++i) {
        cout<<data.at(i).name<<" ";
        cout<<data.at(i).Fei<<" ";
        cout<<data.at(i).Ft<<" ";
        cout<<data.at(i).Fei_minus_Ft<<" ";
        cout<<data.at(i).Fei_minus_Ft_square<<" ";
        cout<<data.at(i).square_div_Ft<<" ";

        cout<<endl;

    }
    cout<<pirs_emp<<endl;

}
