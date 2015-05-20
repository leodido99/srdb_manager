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

void MainWindow::initTabs()
{
    /* For each tables create a new tab with a table view and buttons */
    QSqlTableModel *model = this->manager.getFirsTable();
    while(model != NULL) {
        /* Create new page */
        QWidget *page = new QWidget();
        /* Create new base layout */
        QHBoxLayout *baseLayout = new QHBoxLayout();
        /* Create new Table View to hold the model */
        QTableView *tbl = new QTableView();
        tbl->setModel(model);
        /* Add table view to base layout */
        baseLayout->addWidget(tbl);
        /* Create new vertical layouts for buttons */
        QVBoxLayout *buttonLayout = new QVBoxLayout();
        /* Create new buttons */
        /* Edit */
        QPushButton *editButton = new QPushButton();
        editButton->setText("Edit");
        buttonLayout->addWidget(editButton);
        /* Connect clicked signal */
        //connect(editButton, SIGNAL(clicked()), &this->mapper, SLOT(map()));

        /* Insert */
        QPushButton *insertButton = new QPushButton();
        insertButton->setText("Insert");
        buttonLayout->addWidget(insertButton);
        /* Connect button */
        connect(insertButton, SIGNAL(clicked()), &this->mapper, SLOT(map()));
        this->mapper.setMapping(insertButton, model->tableName());
        /* Add button layout to base layout */
        baseLayout->addLayout(buttonLayout);
        /* Add base layout to the page */
        page->setLayout(baseLayout);
        /* Add new tab */
        ui->tabDBTables->addTab(page, model->tableName());
        /* Get next table in the list */
        model = this->manager.getNextTable();
    }

    /* Connect mapper and insert row function */
    connect(&this->mapper, SIGNAL(mapped(QString)), this, SLOT(insertNewRow(QString)));
}

void MainWindow::insertNewRow(QString table)
{
    /* Find the table view model */
    qDebug() << "Insert New Row " << table;
}

void MainWindow::on_connectDB_clicked()
{    
    if (manager.connect("192.168.1.10","leo","Leon4Rdb","scos2000")) {        
        this->initTabs();
    }
}

void MainWindow::on_connectDB_2_clicked()
{
    if (manager.connect("10.54.36.56","leo","Leon4Rdb","scos2000")) {
        this->initTabs();
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

/*
 *     QSqlTableModel *model = qobject_cast<QSqlTableModel *>(table->model());
    if (!model)
        return;

    QModelIndex insertIndex = table->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    model->insertRow(row);
    insertIndex = model->index(row, 0);
    table->setCurrentIndex(insertIndex);
    table->edit(insertIndex);*/
