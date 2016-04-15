#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    method=0;
    howInput=ui->comboBox_list->currentIndex();

    this->setMaximumSize(648,613);
    this->setMinimumSize(648,613);

    ui->actions->setEnabled(false);

    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);

    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->calculateButton->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(7);

    ui->button_Mann->adjustSize();
    ui->button_Pirson->adjustSize();
    ui->button_K_S->adjustSize();
    //ui->tableWidget->it
    //РИСОВАНИЕ, ПАРАМЕРТЫ
    ui->graphicsView->setBackgroundBrush(Qt::black);
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush lineBrush(Qt::white);
    QPen linePen(Qt::white);
    linePen.setWidth(2);

    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());

    QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem(scene->width()/2,scene->height()/2,50,50);
    ellipse->setStartAngle(0);
    ellipse->setSpanAngle(180);
    ellipse->setPen(linePen);



    scene->addLine(0,ui->graphicsView->height()/2,ui->graphicsView->width(),ui->graphicsView->height()/2,linePen);
    scene->addItem(ellipse);

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

    if(howInput==1){
        ui->table_input->setRowCount(1);
        ui->table_input->setColumnCount(2);
        QTableWidgetItem *header=new QTableWidgetItem();
        header->setText(nameGroup1);
        QTableWidgetItem *header2=new QTableWidgetItem();
        header2->setText(nameGroup2);
        ui->table_input->setHorizontalHeaderItem(0,header);
        ui->table_input->setHorizontalHeaderItem(1,header2);
    }
    else if (howInput ==0) {
        ui->table_input->setRowCount(1);
        ui->table_input->setColumnCount(1);
        QTableWidgetItem *header=new QTableWidgetItem();
        header->setText("Список оценок");

        ui->table_input->setHorizontalHeaderItem(0,header);


    }
    ui->table_input->resizeColumnsToContents();


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

vector<QStringList> MainWindow::getInfoFromFields2(QString str1)
{
    vector<QStringList> students;
    vector<float> studs;

    QStringList group1=str1.split("|");
    students.push_back(group1);

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
    QMessageBox *info=new QMessageBox;
    QString infoString="Проверьте,чтобы файл имел расширение .csv \n";
    infoString.push_back("ИНСТРУКЦИЯ:\n");
    infoString.push_back("При сохранении файла в excel нажмите сохранить как. Далее выберите формат .csv , ок.");

    info->setText(infoString);
    info->exec();
    ui->stackedWidget->setCurrentIndex(1);
    QFileDialog openFile;
    QString path=openFile.getOpenFileName();
    if(path!=NULL){
        vector<QStringList> list=getFromCsv(path);
        fillTable(ui->tableWidget,getFromCsv(path));
        ui->stackedWidget->setCurrentIndex(4);

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
    if(howInput==0){
        ui->comboBox->setEnabled(false);
    }
    else{
        ui->comboBox->setEnabled(true);
    }
    if(howInput==0){
        if(stroka1!=NULL){
         vector<QStringList> students=getInfoFromFields2(stroka1);
         mann->loadDataFromFields(students);
         mann->sortStudents();
         mann->setGroups();
         mann->setRate();
         //mann->showStudents();
         mann->results();
         outputTable(mann->getStudents(),ui->table_output);
         mann->resetVariables();
         students.clear();
         stroka1="";
        }
    }
    else{

    }
    if(stroka1!=NULL && stroka2!=NULL){
        vector<QStringList> students=getInfoFromFields(stroka1,stroka2);
        mann->loadDataFromFields(students);
        mann->sortStudents();

        mann->setRate();
        //mann->showStudents();
        mann->results();
        outputTable(mann->getStudents(),ui->table_output);
        mann->resetVariables();
        students.clear();
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
            if(howInput==0) mann->setGroups();
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
      stroka1=takeString(ui->tableWidget);
    }

    else {
        stroka2="";
        stroka2=takeString(ui->tableWidget);
    }


}

QString MainWindow::takeString(QTableWidget *table){
    QString str=NULL;
    QModelIndexList selectedIndices=table->selectionModel()->selection().indexes();
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

vector<QStringList> MainWindow::getDataFromTable(QTableWidget *table, int groupCount)
{
    vector<QStringList> newData;
    QStringList list;
    QString stroka;

    for (int i = 0; i < groupCount+1; ++i) {
        list.clear();
        stroka.clear();
        for (int j = 0; j < table->rowCount(); ++j) {
            if(table->item(j,i)!=0){
               stroka.push_back(table->item(j,i)->text()+"|");

               cout<<"STROKA!"<<endl;
            }


        }
        stroka.remove(stroka.length()-1,1);
        list=stroka.split("|");
        newData.push_back(list);
        cout<<"Pushed!!"<<endl;
        cout<<stroka.toUtf8().constData()<<endl;

    }
    cout<<"NewData size! "<<newData.at(0).size()<<endl;
    return newData;
}



void MainWindow::outputTable(vector<Student> *students, QTableWidget *table)
{

    table->clear();

    table->setColumnCount(3);
    table->setRowCount(students->size());
    cout<<table->rowCount()<<" rows"<<endl;
    QTableWidgetItem *header=new QTableWidgetItem();
    QTableWidgetItem *header1=new QTableWidgetItem();
    QTableWidgetItem *header2=new QTableWidgetItem();
    QTableWidgetItem *header3=new QTableWidgetItem();
    QTableWidgetItem *header4=new QTableWidgetItem();
    header->setText("Группа");
    table->setHorizontalHeaderItem(0,header);
    header1->setText("Баллы");
    table->setHorizontalHeaderItem(1,header1);
    header2->setText("Ранг");
    table->setHorizontalHeaderItem(2,header2);





    table->resizeColumnsToContents();

    for (int i = 0; i < students->size(); ++i) {
        //QString str1=QString::number(students->at(i).group);
        QTableWidgetItem *item1=new QTableWidgetItem; item1->setText(QString::number(students->at(i).group));
        QTableWidgetItem *item2=new QTableWidgetItem; item2->setText(QString::number(students->at(i).scores));
        QTableWidgetItem *item3=new QTableWidgetItem; item3->setText(QString::number(students->at(i).rate));
        if(students->at(i).group==0){
            QBrush *brush=new QBrush;

            item1->setForeground(Qt::darkBlue);
            item2->setTextColor(Qt::darkBlue);
            item3->setTextColor(Qt::darkBlue);

            item1->setBackgroundColor(Qt::green);
            item2->setBackgroundColor(Qt::green);
            item3->setBackgroundColor(Qt::green);
        }
        else{
            item1->setTextColor(QColor(3,255,255));
            item2->setTextColor(QColor(3,255,255));
            item3->setTextColor(QColor(3,255,255));

            item1->setBackgroundColor(QColor(220,147,32));
            item2->setBackgroundColor(QColor(220,147,32));
            item3->setBackgroundColor(QColor(220,147,32));
        }


        table->setItem(i,0,item1);
        table->setItem(i,1,item2);
        table->setItem(i,2,item3);

    }

    ui->stackedWidget->setCurrentIndex(2);

}



void MainWindow::on_buttonBox_accepted()
{
    /*method=ui->comboSelectMethod->currentIndex();
    cout<<method<<endl;
    howInput=ui->comboBox_list->currentIndex();
    QMessageBox msg;
    msg.setText("Нажмите вкладку 'Операции' и выберите метод ввода");
    msg.exec();
   ui->actions->setEnabled(true);

   ui->table_input->setColumnCount(howInput+1);
   ui->table_input->clearContents();
   //ui->stackedWidget->setCurrentIndex(1);*/
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
    QModelIndexList selection=ui->table_input->selectionModel()->selectedIndexes();
    if(ui->table_input->columnCount()>1) deleteIndeces(&selection);
    sortIndeces(&selection);
    for (int i = 0; i < selection.count(); ++i) {
        ui->table_input->removeRow(selection.at(i).row()-i);

    }
}

void MainWindow::deleteIndeces(QModelIndexList *m)
{
    for (int i = 1; i < m->count(); ++i) {

        if(m->at(i).column()>0 && i>0){
            //QTableWidgetItem *prevItem=ui->table_input->item(m->at(i).row()-i,0);
            if(m->at(i).column()>0 && m->at(i-1).column()==0)
            m->removeAt(i);
        }


    }
}

void MainWindow::sortIndeces(QModelIndexList *m)
{
    for (int i = 0; i < m->count()-1; ++i) {
        for (int j = 0; j < m->count()-i-1; ++j) {
            if(m->at(j).row()>m->at(j+1).row()){
                m->swap(j,j+1);
            }
        }
    }
}

void MainWindow::tableCorrector(QTableWidget *table)
{
    for (int i = 0; i < table->rowCount(); ++i) {
        for (int j = 0; j < table->columnCount(); ++j) {
            if(table->item(i,j)->text().isEmpty()){
                table->removeRow(i);
                break;
            }
        }
    }
}

void MainWindow::on_buttonBox_2_accepted()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_buttonBox_2_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonChangeName_clicked()
{
    if(howInput==1){
        ui->textEdit_3->setVisible(true);
        ui->textEdit_4->setVisible(true);
        ui->textEdit_3->setText(nameGroup1);
        ui->textEdit_4->setText(nameGroup2);
    }
    else{
        ui->textEdit_3->setVisible(true);

        ui->textEdit_3->setText(nameGroup1);

    }

}

void MainWindow::on_textEdit_3_textChanged()
{
    nameGroup1=ui->textEdit_3->toPlainText();
    QTableWidgetItem *header=new QTableWidgetItem();
    header->setText(nameGroup1);

    ui->table_input->setHorizontalHeaderItem(0,header);

}

void MainWindow::on_textEdit_4_textChanged()
{
    nameGroup1=ui->textEdit_3->toPlainText();
    QTableWidgetItem *header=new QTableWidgetItem();
    header->setText(nameGroup1);

    ui->table_input->setHorizontalHeaderItem(0,header);

    nameGroup2=ui->textEdit_4->toPlainText();
    QTableWidgetItem *header2=new QTableWidgetItem();
    header2->setText(nameGroup2);

    ui->table_input->setHorizontalHeaderItem(1,header2);
}

void MainWindow::on_button_calc_clicked()
{
    vector <QStringList> data;
    data=getDataFromTable(ui->table_input,howInput);
    cout<<"DATA SIZE"<<data.size()<<" DATA SIZZZZ "<<data.at(0).at(0).toUtf8().constData()<< endl;
    cout<<"STYDENTY "<<mann->getStudents()->size()<<endl;
    mann->clearStudents();
    mann->loadDataFromFields(data);
    cout<<"STYDENTY "<<mann->getStudents()->size()<<endl;
    mann->sortStudents();
    if(howInput==0) mann->setGroups();
    mann->showStudents();
    mann->setRate();
    mann->showStudents();
    cout<<"Summs "<<mann->getSumScores(0)<<" "<<mann->getSumScores(1)<<endl;
    mann->results();

    outputTable(mann->getStudents(),ui->table_output);
    mann->resetVariables();
    data.clear();
}

void MainWindow::on_button_Mann_clicked()
{
    method=0;
    cout<<method<<endl;
    howInput=ui->comboBox_list->currentIndex();

    ui->actions->setEnabled(true);

    ui->table_input->setColumnCount(howInput+1);
    ui->table_input->clearContents();
}

void MainWindow::on_button_Pirson_clicked()
{
    ui->table_pirson->clear();
    ui->table_pirson->clearContents();
    cout<<"cleared"<<endl;

    ui->table_pirson->setColumnCount(2);
    ui->table_pirson->setRowCount(1);

    QTableWidgetItem *header1=new QTableWidgetItem;
    QTableWidgetItem *header2=new QTableWidgetItem;
    header1->setText("Название");
    ui->table_pirson->setHorizontalHeaderItem(0,header1);
    header2->setText("F эi");
    ui->table_pirson->setHorizontalHeaderItem(1,header2);

    //ui->table_pirson->adjustSize();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_button_pirson_addrow_clicked()
{
    ui->table_pirson->insertRow(ui->table_pirson->rowCount());
}

void MainWindow::on_button_pirson_deleterow_clicked()
{
    ui->table_pirson->removeRow(ui->table_pirson->rowCount()-1);
}

void MainWindow::on_button_pirson_calc_clicked()
{
    QMessageBox info;
    info.setText("Неправильно заполненные строки будут удалены!");
    info.exec();
    tableCorrector(ui->table_pirson);
    cout<<ui->table_pirson->rowCount()<<endl;

    pirson->setData(ui->table_pirson);
    pirson->showData();
}
