#include "pirson.h"

Pirson::Pirson()
{

}

void Pirson::setData(QTableWidget *table)
{
    n=0;
    k=0;
    k=table->rowCount();
    for (int i = 0; i < k; ++i) {
        Object newObject{};
        newObject.name=table->item(i,0)->text().toUtf8().constData();
        newObject.Fei=table->item(i,1)->text().toDouble();
        data.push_back(newObject);
        n+=table->item(i,1)->text().toDouble();
        k+=1;
    }
    for (int j = 0; j < data.size(); ++j) {
        data.at(j).Ft=n/k;
        data.at(j).Fei_minus_Ft=data.at(j).Fei-data.at(j).Ft;
        data.at(j).Fei_minus_Ft_square=pow(data.at(j).Fei_minus_Ft,2);
        data.at(j).square_div_Ft=data.at(j).Fei_minus_Ft_square / data.at(j).Ft;
    }
}
