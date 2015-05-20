#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


#include "recorddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager.setLogListView(ui->listLog);
}

MainWindow::~MainWindow()
{
    manager.close();
    delete ui;
}

void MainWindow::on_connectDB_clicked()
{    
    if (manager.connect("192.168.1.10","leo","Leon4Rdb","scos2000")) {        
        this->initTabs();

        /* Link database PCF table to table view */
        //ui->tblPCF->setModel(manager.getPCFModel());
    }
}

void MainWindow::on_newparam_clicked()
{
    scPCF parameter;
    parameter.name = "magggu";
    parameter.paramFormatCode = 1;
    parameter.paramTypeCode = 1;
    parameter.category = "C";
    parameter.nature = "B";
    manager.newParameter(parameter);
}

void MainWindow::on_getparam_clicked()
{
    manager.getParameters();
}

void MainWindow::on_btnNewPCFRec_clicked()
{
    RecordDialog tst("PCF",manager.getSQLRecord(PCF));
    tst.exec();
    // Connect to signal updatedRecord to get back the update record
}

void MainWindow::on_connectDB_2_clicked()
{
    if (manager.connect("10.54.36.56","leo","Leon4Rdb","scos2000")) {
        this->initTabs();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QSqlRecord record;
    QSqlField field;
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour1");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test12");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour3");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test14");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour5");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test16");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour7");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test18");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour9");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test10");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour0");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test11");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour12");
    record.append(field);
    field.setType(QVariant::String);
    RecordDialog tst("PCF", record);
    tst.exec();
}

void MainWindow::initTabs()
{
    /* For each tables create a new tab with a table view */   
    QSqlTableModel *model = this->manager.getFirsTable();
    while(model != NULL) {
        QTableView *tbl = new QTableView();
        tbl->setModel(model);
        /* Add new tab */
        ui->tabDBTables->addTab(tbl, model->tableName());

        model = this->manager.getNextTable();
    }


    /*
     *        for(int i=0; i < manager.getNbTables(); i++) {
            QTableView *tbl = new QTableView();
            tbl->setModel(manager.getPCFModel());
            ui->tabDBTables->addTab(tbl, "Table");
        }
     */
}
