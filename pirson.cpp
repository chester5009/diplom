#include "pirson.h"

void Pirson::initTables()
{

}

Pirson::Pirson()
{
    pirson_t1=new float[80]{3.841,
                         5.991,
                         7.815,
                         9.488,
                         11.07,
                         12.59,
                         14.07,
                         15.51,
                         16.92,
                         18.31,
                         19.68,
                         21.03,
                         22.36,
                         23.68,
                         25,
                         26.3,
                         27.59,
                         28.87,
                         30.14,
                         31.41,
                         32.67,
                         33.92,
                         35.17,
                         36.42,
                         37.65,
                         38.89,
                         40.11,
                         41.34,
                         42.56,
                         43.77,
                         44.99,
                         46.19,
                         47.4,
                         48.6,
                         49.8,
                         51,
                         52.19,
                         53.38,
                         54.57,
                         55.76,
                         56.94,
                         58.12,
                         59.3,
                         60.48,
                         61.66,
                         62.83,
                         64,
                         65.17,
                         66.34,
                         67.5,
                         68.67,
                         69.83,
                         70.99,
                         72.15,
                         73.31,
                         74.47,
                         75.62,
                         76.78,
                         77.93,
                         79.08,
                         80.23,
                         81.38,
                         82.53,
                         83.68,
                         84.82,
                         85.96,
                         87.11,
                         88.25,
                         89.39,
                         90.53,
                         91.67,
                         92.81,
                         93.95,
                         95.08,
                         96.22,
                         97.35,
                         98.48,
                         99.62,
                         100.75,
                         101.88};
    pirson_t2=new float[80]{6.635,
                         9.21,
                         11.34,
                         13.28,
                         15.09,
                         16.81,
                         18.48,
                         20.09,
                         21.67,
                         23.21,
                         24.72,
                         26.22,
                         27.69,
                         29.14,
                         30.58,
                         32,
                         33.41,
                         34.81,
                         36.19,
                         37.57,
                         38.93,
                         40.29,
                         41.64,
                         42.98,
                         44.31,
                         45.64,
                         46.96,
                         48.28,
                         49.59,
                         50.89,
                         52.19,
                         53.49,
                         54.78,
                         56.06,
                         57.34,
                         58.62,
                         59.89,
                         61.16,
                         62.43,
                         63.69,
                         64.95,
                         66.21,
                         67.46,
                         68.71,
                         69.96,
                         71.2,
                         72.44,
                         73.68,
                         74.92,
                         76.15,
                         77.39,
                         78.62,
                         79.84,
                         81.07,
                         82.29,
                         83.51,
                         84.73,
                         85.95,
                         87.17,
                         88.38,
                         89.59,
                         90.8,
                         92.01,
                         93.22,
                         94.42,
                         95.63,
                         96.83,
                         98.03,
                         99.23,
                         100.43,
                         101.62,
                         102.82,
                         104.01,
                         105.2,
                         106.39,
                         107.58,
                         108.77,
                         109.96,
                         111.14,
                         112.33};
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
    cout<<pirson_t1[(int)k-2]<<" "<<pirson_t2[(int)k-2]<<endl;

    QString results;

}
