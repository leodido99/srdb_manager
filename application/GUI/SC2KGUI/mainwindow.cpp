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
        qDebug() << "DBG: Connected to database!";

        /* Link database PCF table to table view */
        ui->tblPCF->setModel(manager.getPCFModel());
    } else {
        qDebug() << "DBG: Could not connect to database!";
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
        qDebug() << "DBG: Connected to database!";

        /* Link database PCF table to table view */
        ui->tblPCF->setModel(manager.getPCFModel());
    } else {
        qDebug() << "DBG: Could not connect to database!";
    }
}

void MainWindow::on_pushButton_clicked()
{
    QSqlRecord record;
    QSqlField field;
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    field.setName("test1");
    field.setType(QVariant::String);
    record.append(field);
    field.setName("bonjour");
    record.append(field);
    field.setType(QVariant::String);
    RecordDialog tst("PCF", record);
    tst.exec();
}
