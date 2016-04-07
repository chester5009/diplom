#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    method=ui->comboSelectMethod->currentIndex();

    this->setMaximumSize(648,613);
    this->setMinimumSize(648,613);

    ui->actions->setEnabled(false);

    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->calculateButton->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(7);
    //ui->tableWidget->it

    mann->showStudents();
    mann->sortStudents();
    mann->showStudents();
    mann->setRate();
    mann->showStudents();

    //Загрузка таблиц 001 005 критических значений.

    /*vector<QStringList> list;
    list=getFromCsv("table001.csv");
    mann->setTable(list,0);
    list=getFromCsv("table005.csv");
    mann->setTable(list,1);*/

    //mann->showTable(mann->table005);
    //mann->showTableCell(mann->table005,20,20);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_exit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_action_input_triggered()
{
    ui->textEdit->setEnabled(true);
    ui->textEdit_2->setEnabled(true);
    ui->calculateButton->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(1);

    ui->table_input->setRowCount(1);
    ui->table_input->setColumnCount(2);
}

vector<QStringList> MainWindow::getInfoFromFields(QString str1, QString str2){
     vector<QStringList> students;
     vector<float> studs;

     QStringList group1=str1.split("|");
     QStringList group2=str2.split("|");
     students.push_back(group1);
     students.push_back(group2);
     //group1.at(0).toUtf8().
     //cout<<students.at(0).at(2).toInt()+21<<endl;

     return students;
}

void MainWindow::on_calculateButton_clicked()
{
    vector<QStringList> students=getInfoFromFields(ui->textEdit->toPlainText(),ui->textEdit_2->toPlainText());
    mann->loadDataFromFields(students);
    mann->sortStudents();
    mann->setRate();
    mann->showStudents();
    mann->results();

}

void MainWindow::on_action_csv_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    QFileDialog openFile;
    QString path=openFile.getOpenFileName();
    if(path!=NULL){
        vector<QStringList> list=getFromCsv(path);
        fillTable(ui->tableWidget,getFromCsv(path));

    }




}

vector<QStringList> MainWindow::getFromCsv(QString path){
    vector<QStringList> fileDate;

    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly);
    cout<<"FilePath - "<<path.toUtf8().constData()<<endl;
    while(!file.atEnd()){
        QString str= file.readLine();
        str.replace(',','.');
        QStringList oneString=str.split(';');
        cout<<str.toUtf8().constData()<<endl;
        fileDate.push_back(oneString);
    }
    file.close();

    return fileDate;
}
void MainWindow::fillTable(QTableWidget *table, vector<QStringList> list){
    table->setColumnCount(list.at(0).size());
    table->setRowCount(list.size());
    for(int i=0;i<list.size();++i){
        for (int j = 0; j < list.at(i).size(); ++j) {
            QTableWidgetItem *item=new QTableWidgetItem;
            item->setText(list.at(i).at(j));
            table->setItem(i,j,item);
        }
    }
}

/*void MainWindow::on_pushButton_clicked(){
cout<<"Hell"<<endl;
}*/

void MainWindow::on_calculateButton2_clicked()
{

    //cout<<"Orientation "<<getTableOrientation()<<endl;
    //cout<<"Hello"<<endl;
    if(stroka1!=NULL && stroka2!=NULL){
        vector<QStringList> students=getInfoFromFields(stroka1,stroka2);
        mann->loadDataFromFields(students);
        mann->sortStudents();
        mann->setRate();
        //mann->showStudents();
        mann->results();
        stroka1="";
        stroka2="";
    }
}
//взять данные из выделенной таблицы ,определить ориентацию таблицы,
int MainWindow::getTableOrientation(){
    QModelIndexList selectedIndices=ui->tableWidget->selectionModel()->selection().indexes();
    cout<<"Selected :"<<endl;
    QString str1,str2;
    for (int i = 0; i < selectedIndices.count(); ++i) {
        QModelIndex index=selectedIndices.at(i);
        cout<<index.row()<<" "<<index.column()<<endl;
    }

    if(selectedIndices.size()>0){
        if(selectedIndices.at(selectedIndices.count()-1).column()-selectedIndices.at(0).column()==1){
            for (int i = 0; i < selectedIndices.count(); ++i) {
                int iRow=selectedIndices.at(i).row();
                int iCol=selectedIndices.at(i).column();
                if(selectedIndices.at(i).column()==selectedIndices.at(0).column()){
                    str1+=ui->tableWidget->item(iRow,iCol)->text()+",";
                    //if(i==selectedIndices.count()-1)str1.remove(i==selectedIndices.count()-1,1);
                }
                else{
                    str2+=ui->tableWidget->item(iRow,iCol)->text()+",";
                    //if(i==selectedIndices.count()-1)str2.remove(i==selectedIndices.count()-1,1);
                }


            }
            str1.remove(selectedIndices.count()-1,1);
            str2.remove(selectedIndices.count()-1,1);
            cout<<"Q Len "<<str1.toUtf8().constData()<<" "<<str2.toUtf8().constData()<<endl;
            getInfoFromFields(str1,str2);
            vector<QStringList> students=getInfoFromFields(str1,str1);
            mann->loadDataFromFields(students);
            mann->sortStudents();
            mann->setRate();
            //mann->showStudents();
            mann->results();

            return 0;//Вертикальная ориентация таблицы
        }
        else if(selectedIndices.at(selectedIndices.count()-1).row()-selectedIndices.at(0).row()==1){
            for (int i = 0; i < selectedIndices.count(); ++i) {
                int iRow=selectedIndices.at(i).row();
                int iCol=selectedIndices.at(i).column();
                if(selectedIndices.at(i).row()==selectedIndices.at(0).row()){
                    str1+=ui->tableWidget->item(iRow,iCol)->text()+",";
                    //if(i==selectedIndices.count()-1)str1.remove(i==selectedIndices.count()-1,1);
                }
                else{
                    str2+=ui->tableWidget->item(iRow,iCol)->text()+",";
                    //if(i==selectedIndices.count()-1)str2.remove(i==selectedIndices.count()-1,1);
                }


            }
            str1.remove(str1.count(),1);
            str2.remove(str2.count(),1);
            cout<<"Q Len "<<str1.toUtf8().constData()<<" "<<str2.toUtf8().constData()<<endl;
            getInfoFromFields(str1,str2);
            vector<QStringList> students=getInfoFromFields(str1,str2);
            mann->loadDataFromFields(students);
            mann->sortStudents();
            mann->setRate();
            //mann->showStudents();
            mann->results();
            return 1;//Горизонтальная ориентация таблицы
        }
    }
    return -1;

}

void MainWindow::on_addButton_clicked()
{
    if(ui->comboBox->currentIndex()==0){
      stroka2="";
      stroka1=takeString();
    }

    else {
        stroka2="";
        stroka2=takeString();
    }


}

QString MainWindow::takeString(){
    QString str=NULL;
    QModelIndexList selectedIndices=ui->tableWidget->selectionModel()->selection().indexes();
    cout<<"Selected :"<<endl;
    for(int i=0;i<selectedIndices.count();++i){
        int iRow=selectedIndices.at(i).row();
        int iCol=selectedIndices.at(i).column();
        str.push_back(ui->tableWidget->item(iRow,iCol)->text()+"|");

    }
    str.remove(str.length()-1,1);
    str.replace(',','.');
    cout<<str.toUtf8().constData()<<endl;
    return str;
}



void MainWindow::on_buttonBox_accepted()
{
    method=ui->comboSelectMethod->currentIndex();
    cout<<method<<endl;

    QMessageBox msg;
    msg.setText("Нажмите вкладку 'Операции' и выберите метод ввода");
    msg.exec();
   ui->actions->setEnabled(true);
   //ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox helpMessage;
    helpMessage.setText("текст с руководством программы");
    helpMessage.setStandardButtons(QMessageBox::Ok);
    helpMessage.exec();
}



void MainWindow::on_table_input_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{

}

void MainWindow::on_pushButton_clicked()
{
   ui->table_input->insertRow(ui->table_input->rowCount());
}

void MainWindow::on_pushButton_2_clicked()
{

}
