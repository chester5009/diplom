#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(648,613);
    this->setMinimumSize(648,613);
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->calculateButton->setEnabled(false);




    mann->showStudents();
    mann->sortStudents();
    mann->showStudents();
    mann->setRate();
    mann->showStudents();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QCoreApplication::quit();

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


}

vector<QStringList> MainWindow::getInfoFromFields(QString str1, QString str2){
     vector<QStringList> students;
     vector<float> studs;

     QStringList group1=str1.split(",");
     QStringList group2=str2.split(",");
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
