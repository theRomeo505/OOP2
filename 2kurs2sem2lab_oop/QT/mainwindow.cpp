#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include <thread>
#include <mutex>
#include "string"
#include <vector>
#include "sorts.h"
#include "QtDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->listWidget_2->count()<32767)
    ui->listWidget_2->addItem(ui->spinBox->text());
    else qDebug() << "ERROR\n";
}
void MainWindow::add_items_to_lw2(int num){
    for (int i=0; i<num;i++){
         ui->listWidget_2->addItem(QString::fromStdString(std::to_string(rand()%32767)));
    }
}
void MainWindow::old_func(){
    ui->listWidget_2->clear();
    srand(time(NULL));
    if (ui->spinBox_2->value()>0){
        for (int i=0;i<ui->spinBox_2->value();i++){
            ui->listWidget_2->addItem(QString::fromStdString(std::to_string(rand()%32767)));
        }
    }
}
void MainWindow::on_pushButton_4_clicked()
{
    unsigned num_of_threads=std::thread::hardware_concurrency();
    int s=1;
    int size=ui->spinBox_2->value()/num_of_threads;
    if (size*num_of_threads!=ui->spinBox_2->value()) s= ui->spinBox_2->value()-size*num_of_threads;
    std::vector<std::thread> threads(num_of_threads);
    for (int i=0;i<num_of_threads;i++){
        if (s!=0){
        threads[i]=std::thread(add_items_to_lw2,size+1);
        s--;
        }
        else
            threads[i]=std::thread(add_items_to_lw2,size);
    }
   // old_func();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget_2->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (ui->listWidget->selectedItems().size()!=0){
        if (ui->listWidget_2->count()>1){
            vector<int> data(ui->listWidget_2->count(),0);
            for (int i=0;i<ui->listWidget_2->count();i++){
                data[i]=ui->listWidget_2->item(i)->text().toInt();
            }
            sortClass temp;
            switch(ui->listWidget->currentRow()){
            case 0: temp.bubbleSort(data) ;break; //bubble
            case 1: temp.ShakerSort(data) ;break; //shaker
            case 2: temp.heapSort(data) ;break; //heap
            case 3: temp.quickSort(data,0,data.size()-1) ;break; //quick
            case 4: temp.mergeSort(data,0,data.size()-1); break; // merge
            }
            ui->listWidget_2->clear();
            for (int i=0;i<data.size();i++){
                ui->listWidget_2->addItem(QString::fromStdString(std::to_string(data[i])));
            }
        }
    }
    else {
        qDebug() << "ERROR\n";
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if ((ui->listWidget_4->selectedItems().size()!=0 && ui->listWidget_5->selectedItems().size()!=0)){
        if (!(ui->listWidget_4->currentRow()==ui->listWidget_5->currentRow())){
            if (ui->listWidget_2->count()>1){
                vector<int> data(ui->listWidget_2->count(),0);
                for (int i=0;i<ui->listWidget_2->count();i++){
                    data[i]=ui->listWidget_2->item(i)->text().toInt();
                }
                sortClass temp;
                ui->listWidget_3->clear();
                ui->listWidget_3->addItem(QString::fromStdString(std::to_string(temp.difference(data,ui->listWidget_4->currentItem()->text().toStdString(),ui->listWidget_5->currentItem()->text().toStdString()))));
            }
        }
        else qDebug() << "ERROR\n";
    }
    else qDebug() << "ERROR\n";
}
