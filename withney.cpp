#include "withney.h"
#include <cstdlib>
#include <ctime>
#include <tables.h>
vector<Student> *Withney::getStudents() const
{
    return students;
}

Withney::Withney()
{

}

void Withney::createStudents(int count){
    int newCount=count;
    if(newCount % 2 !=0)newCount++;
    cout<<"count ="<<newCount<<endl;
    int group=0;
    srand(time(0));//обнуление rand
    for(int i=0;i<newCount;i++){

      Student oneStud{group,rand()%60+40,0};
      if(group==0)group=1;
      else {
          group=0;
      }
      this->addStudent(oneStud);
      //cout<<oneStud.scores<<endl;
    }


}

//Добавить студента
void Withney::addStudent(Student newStudent){
    this->students->push_back(newStudent);
}
//Очистить список студентов
void Withney::clearStudents(){
    this->students->clear();
}
//Вывод списка студентов
void Withney::showStudents(){
    for (int i = 0; i < students->size(); ++i) {
        cout<<i+1<<": "<<students->at(i).group<<" "<<students->at(i).scores<<" "<<students->at(i).rate<<endl;
    }
    cout<<endl;

}

//Сортировка списка студентов по возрастанию баллов
void Withney::sortStudents(){
    for(int i=0;i<students->size();i++){
        for(int j=i+1;j<students->size();j++){
            if(students->at(j).scores <students->at(i).scores )swap(students->at(i),students->at(j));
        }
    }
}

//Подсчет рейтинга для каждого студента
void Withney::setRate(){
    float rate=0;
    float count=0;
    //Обход студентов
    for (int i = 0; i < students->size(); ++i) {

        if(i>0 && i<students->size()-1){
            if(students->at(i).scores==students->at(i-1).scores){
                rate+=i+1;
                count+=1;
            }
            else {
                for(int j=0;j<count;j++){
                    cout<<"info "<<rate<<" "<<count<<" "<<i-j-1<<endl;
                    students->at(i-j-1).rate=rate/count;
                }
                count=1;
                rate=i+1;
            }
        }
        else if (i==students->size()-1) {
            if(students->at(i).scores==students->at(i-1).scores){
                rate+=i+1;
                count+=1;
                for(int j=0;j<count;j++){
                    //cout<<"info "<<rate<<" "<<count<<" "<<i-j<<endl;
                    students->at(i-j).rate=rate/count;
                }

               // rate=i+1;
                students->at(i).rate=rate/count;
            }
            else {
                for(int j=0;j<count;j++){
                    //cout<<"info "<<rate<<" "<<count<<" "<<i-j-1<<endl;
                    students->at(i-j-1).rate=rate/count;
                }
                count=1;
                rate=i+1;
                students->at(i).rate=rate/count;
            }
        }
        else {

            rate+=i+1;
            count+=1;
        }

    }
}

void Withney::loadDataFromFields(vector<QStringList> s){

    for(int i=0;i<s.size();i++){
        for (int j = 0; j < s.at(i).size(); ++j) {
            Student newStudent{i,s.at(i).at(j).toFloat(),0};
            //cout<<"UFO "<<s.at(i).at(j).toFloat()<<endl;
            students->push_back(newStudent);
            //<<"PUSHED STUD"<<endl;
        }
    }
}

void Withney::results(){
    setlocale(LC_ALL, "rus");
    float sum1=0,sum2=0;
    int n1=0,n2=0,nx=0;
    float Tx=0;
    for(int i=0;i<students->size();i++){
        if(students->at(i).group==0) {
            n1++;
            sum1+=students->at(i).rate;
        }
        else {
            n2++;
            sum2+=students->at(i).rate;
        }
    }
    if(sum1<sum2){
        Tx=sum2;
        nx=n2;
    }
    else {
        Tx=sum1;
        nx=n1;
    }
    cout<<"Premennye "<<n1<<" "<<n2<<" "<<nx<<" "<<Tx<<" "<<sum1<<" "<<sum2<<endl;
    float res=calculateWithney(n1,n2,nx,Tx);

    float Uemp001=mann_t1[n1-3][n2-2];   //this->table001->at(n1-3).at(n2-2);
    float Uemp005=mann_t2[n1-3][n2-2];   //this->table005->at(n1-3).at(n2-2);
    cout<<"UEmp001= "<<Uemp001<<" UEmp005= "<<Uemp005<<endl;

    string itog1="Group 2  DOES NOT exceed Group 1 the level of nonverbal intelligence";
    string itog2="Group 2  exceeds Group 1 the level of non-verbal intelligence";
    QString results="Mann = "+QString::number(res)+" ";
    //string itog3="Group 1 EQUAL group 2";
    if(res>=Uemp005){
       cout<<"Mann !! "<<res<<" "<<itog1<<endl;
       results+=QString::fromStdString(itog1);
    }
    else if(res<Uemp005){
       cout<<"Mann !! "<<res<<" "<<itog2<<endl;
       results+=QString::fromStdString(itog2);
    }
    else{
      // cout<<"Mann !! "<<res<<" "<<itog3<<endl;
    }
    //QFileDialog openFile;

    //QString path=openFile.getExistingDirectory();
    QPrinter printer;

    printer.setOutputFileName("output.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);

    QPainter painter(&printer);
    QPen pen;
    pen.setWidth(14);
    pen.setColor(Qt::blue);
    QFont font;
    font.setPixelSize(18);

    painter.setFont(font);
    //pen.setBrush(Qt::SolidLine);
    painter.setPen(pen);

    painter.drawText(30,30,results);


    //resetVariables();
}

void Withney::setTable(vector<QStringList> data, int index){
    vector<vector<float> > *newTable=new  vector< vector<float> > ;
    cout<<"Razmer STROKI "<< data.size()<< " "<<data.at(0).size()<<endl;
    for (int i = 0; i < data.size(); ++i) {
        vector<float> oneRow;
        for (int j = 0; j < data.at(i).size(); ++j) {
            if(data.at(i).at(j)=="-")oneRow.push_back(-1);
            else oneRow.push_back(data.at(i).at(j).toFloat());
        }
        newTable->push_back(oneRow);
    }
    cout<<"Razmer TABLISY "<< newTable->size()<< " "<<newTable->at(0).size()<<endl;
    cout<<newTable->at(0).at(0)<<endl;
    switch (index) {
    case 0:
        this->table001=newTable;
        break;
    case 1:
        this->table005=newTable;
        break;
    default:
        break;
    }
    //this->table005=newTable;
}

void Withney::showTable(vector<vector<float> > *table){
        cout<<" HELLO"<<endl;
        cout<<table->at(0).at(0)<<endl;
        /*for (int i = 0; i < table->size(); ++i) {
            for (int j = 0; j < table->at(i).size(); ++j) {
                cout<<table->at(i).at(j)<<" ";
            }
            //cout<<endl;
        }*/

}

void Withney::showTableCell(vector<vector<float> > *table, int row, int col){
       cout<<table->at(row-3).at(col-2)<<" ";
       cout<<endl;
}

void Withney::setGroups()
{
    int size=getStudents()->size();
    for (int i = 0; i < size; ++i) {
        if(i*2<size) setGroupStudent(i,1);
        else setGroupStudent(i,0);
    }
}

int Withney::getSumScores(int group)
{
    int sumScores=0;
    for (int i = 0; i < getStudents()->size(); ++i) {
        if(getStudents()->at(i).group==group){
            sumScores+=getStudents()->at(i).scores;
        }
    }
    return sumScores;
}

void Withney::setGroupStudent(int index,int group)
{
    getStudents()->at(index).group=group;
}

void Withney::resetVariables(){
    this->students->clear();

}

float Withney::calculateWithney(int n1,int n2,int nx,float Tx){

    return n1*n2+(nx*(nx+1)/2)-Tx;
}
