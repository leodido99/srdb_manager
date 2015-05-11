#include "sc2kdbmanager.h"
#include <QListWidgetItem>

SC2KDBManager::SC2KDBManager()
{

}

bool SC2KDBManager::connect(QString host, QString userName, QString password, QString databaseName)
{
    bool result;

    this->db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);
    result = db.open();
    if (result) {
        this->init();
        /* Print tables */
        qDebug() << this->db.tables(QSql::Tables);
        this->writeLog(QString("Connected to database %1 on %2").arg(databaseName,host));
    }
    return result;
}

bool SC2KDBManager::newParameter(scPCF data)
{
    QSqlRecord record = this->PCFModel->record();
    qDebug() << "record: " << record;

    /* Modify record */
    /* PCF_NAME, PCF_DESCR, PCF_PID, PCF_UNIT, PCF_PTC, PCF_PFC, PCF_WIDTH, PCF_VALID,
     * PCF_RELATED, PCF_CATEG, PCF_NATUR, PCF_CURTX, PCF_INTER, PCF_USCON, PCF_DECIM,
     * PCF_PARVAL, PCF_SUBSYS, PCF_VALPAR, PCF_SPTYPE, PCF_CORR, PCF_OBTID, PCF_DARC, PCF_ENDIAN */
    record.setValue("PCF_NAME", data.name);
    record.setValue("PCF_PTC", data.paramTypeCode);
    record.setValue("PCF_PFC", data.paramFormatCode);
    record.setValue("PCF_CATEG", data.category);
    record.setValue("PCF_NATUR", data.nature);

    /* To get automatic value from db */
    record.setGenerated("PCF_INTER",false);



    /* Insert new record */
    if (!this->PCFModel->insertRecord(-1, record)) {
        qDebug() << "Could not insert record";
    } else {
        this->writeLog(QString("Created new parameter %1").arg(record.value("PCF_NAME").toString()));
    }

    /* Submit changes*/
    this->PCFModel->submitAll();

            /*model.insertRows(row, 1);
            model.setData(model.index(row, 0), 1013);
            model.setData(model.index(row, 1), "Peter Gordon");
            model.setData(model.index(row, 2), 68500);
            model.submitAll();*/





    return true;
}

long SC2KDBManager::getNbParameters()
{
    return this->PCFModel->rowCount();
}

void SC2KDBManager::getParameters()
{


    this->PCFModel->select();
    qDebug() << "PCFModel:" << this->getNbParameters();

    /*QSqlQueryModel model;
    model.setQuery("SELECT * FROM PCF");

    qDebug() << "nb row" <<  model.rowCount();
    for (int i = 0; i < model.rowCount(); ++i) {
        //int id = model.record(i).value("PCF_NAME").toInt();
        QString name = model.record(i).value("PCF_NAME").toString();
        QString description = model.record(i).value("PCF_DESCR").toString();
        qDebug() << name << description;
    }*/
}

void SC2KDBManager::setLogListView(QListWidget *log)
{
    this->log = log;
}

QSqlRecord SC2KDBManager::getSQLRecord(scTables table)
{
    QSqlTableModel *model;
    switch(table) {
        case PCF:
            model = this->PCFModel;
            break;
        default:
        qDebug() << "Unknown table";
            break;
    }
    if (model != NULL) {
        return model->record();
    } else {
        return *(new QSqlRecord);
    }
}

QSqlTableModel* SC2KDBManager::getPCFModel()
{
    return (this->PCFModel);
}

void SC2KDBManager::close()
{
    this->db.close();
}

bool SC2KDBManager::checkPCFMandatory(scPCF data)
{
    /* TODO */
    return true;
}

void SC2KDBManager::init()
{
    this->PCFModel = new QSqlTableModel(NULL, this->db);
    this->PCFModel->setTable("PCF");
    if (!this->PCFModel->select()) {
        qDebug() << "Error during select : " << this->PCFModel->lastError().text();
    }
    qDebug() << "PCFModel:" << this->PCFModel->rowCount();
}

void SC2KDBManager::writeLog(QString msg)
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(msg);
    this->log->addItem(newItem);
}

/* Read from DB */
/*
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM PCF");

    qDebug() << "nb row" <<  model.rowCount();
    for (int i = 0; i < model.rowCount(); ++i) {
        int id = model.record(i).value("PCF_NAME").toInt();
        QString name = model.record(i).value("PCF_NAME").toString();
        qDebug() << id << name;
    }
    return true;
*/
