#include "withney.h"
#include <cstdlib>
#include <ctime>
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
        }
    }
}

void Withney::results(){
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
    cout<<"Mann !! "<<res<<endl;
}

float Withney::calculateWithney(int n1,int n2,int nx,float Tx){

    return n1*n2+(nx*(nx+1)/2)-Tx;
}
