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
    /* Remove all tabs */
    this->deleteTabs();
    /* For each tables create a new tab with a table view and buttons */
    QSqlTableModel *model = this->manager.getFirsTable();
    /* The tab Widget */
    QTabWidget *tabWidget = ui->tabDBTables;
    while(model != NULL) {
        /* Set model to update manually only */
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        /* Create new page */
        QWidget *page = new QWidget();
        /* Create new base layout */
        QHBoxLayout *baseLayout = new QHBoxLayout();
        /* Create new Table View to hold the model */
        QTableView *tbl = new QTableView();
        tbl->setModel(model);
        tbl->resizeColumnsToContents();
        tbl->sortByColumn(0);
        tbl->setSortingEnabled(true);
        /* Add table view to hash */
        this->hashTbl[model->tableName()] = tbl;
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
        connect(insertButton, SIGNAL(clicked()), &this->mapperInsert, SLOT(map()));
        this->mapperInsert.setMapping(insertButton, model->tableName());

        /* Update Table */
        QPushButton *updateButton = new QPushButton();
        updateButton->setText("Send Update");
        buttonLayout->addWidget(updateButton);
        /* Connect button */
        connect(updateButton, SIGNAL(clicked()), &this->mapperUpdate, SLOT(map()));
        this->mapperUpdate.setMapping(updateButton, model->tableName());

        /* Revert changes */
        QPushButton *revertButton = new QPushButton();
        revertButton->setText("Revert Changes");
        buttonLayout->addWidget(revertButton);
        /* Connect button */
        connect(revertButton, SIGNAL(clicked()), &this->mapperRevert, SLOT(map()));
        this->mapperRevert.setMapping(revertButton, model->tableName());

        /* Add button layout to base layout */
        baseLayout->addLayout(buttonLayout);
        /* Add base layout to the page */
        page->setLayout(baseLayout);
        /* Add new tab */
        tabWidget->addTab(page, model->tableName());
        /* Get next table in the list */
        model = this->manager.getNextTable();
    }

    /* Connect mapper */
    connect(&this->mapperInsert, SIGNAL(mapped(QString)), this, SLOT(insertNewRow(QString)));
    connect(&this->mapperUpdate, SIGNAL(mapped(QString)), this, SLOT(submitChanges(QString)));
    connect(&this->mapperRevert, SIGNAL(mapped(QString)), this, SLOT(revertChanges(QString)));
}

void MainWindow::deleteTabs()
{
    qDebug() << "Deleting" << this->ui->tabDBTables->count() << " tabs";
    for(unsigned int i=0; i < (unsigned int)this->ui->tabDBTables->count(); i++) {
        ui->tabDBTables->widget(i)->close();
        ui->tabDBTables->removeTab(i);
    }
}

void MainWindow::writeLog(QString msg)
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(msg);
    ui->listLog->addItem(newItem);
}

void MainWindow::insertNewRow(QString table)
{
    qDebug() << "Insert New Row" << table;

    /* Insert row */
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(this->hashTbl[table]->model());
    if (!model) {
        return;
    }
    QModelIndex insertIndex = this->hashTbl[table]->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    model->insertRow(row);
    insertIndex = model->index(row, 0);
    this->hashTbl[table]->setCurrentIndex(insertIndex);
    this->hashTbl[table]->edit(insertIndex);
}

void MainWindow::submitChanges(QString table)
{
    /* Submit all changes */
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(this->hashTbl[table]->model());
    if (!model) {
        return;
    }
    if (model->submitAll()) {        
        this->writeLog(QString("Changes submitted"));
    } else {        
        this->writeLog(QString("Could not submit changes : %2 - %1").arg(model->lastError().databaseText(), model->lastError().driverText()));
    }
}

void MainWindow::revertChanges(QString table)
{
    /* Revert all changes */
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(this->hashTbl[table]->model());
    if (!model) {
        return;
    }
    model->revertAll();
    qDebug() << "Changes Reverted";
}

void MainWindow::on_connectDB_clicked()
{    
    if (manager.connect("192.168.1.10","leo","Leon4Rdb","scos2000")) {        
        this->initTabs();
    }
}

void MainWindow::on_connectDB_2_clicked()
{
    if (manager.connect("10.54.36.56","leo","Leon4Rdb","scos2k_import")) {
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

void MainWindow::on_pushButton_2_clicked()
{
    this->manager.close();
    this->deleteTabs();
}
