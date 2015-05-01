#include "sc2kdbmanager.h"

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
    }
    return result;
}

bool SC2KDBManager::newParameter(scPCF data)
{





            /*model.insertRows(row, 1);
            model.setData(model.index(row, 0), 1013);
            model.setData(model.index(row, 1), "Peter Gordon");
            model.setData(model.index(row, 2), 68500);
            model.submitAll();*/



   /* QSqlQueryModel model;
    model.setQuery("INSERT INTO PCF");*/

    /* PCF_NAME, PCF_DESCR, PCF_PID, PCF_UNIT, PCF_PTC, PCF_PFC, PCF_WIDTH, PCF_VALID,
     * PCF_RELATED, PCF_CATEG, PCF_NATUR, PCF_CURTX, PCF_INTER, PCF_USCON, PCF_DECIM,
     * PCF_PARVAL, PCF_SUBSYS, PCF_VALPAR, PCF_SPTYPE, PCF_CORR, PCF_OBTID, PCF_DARC, PCF_ENDIAN */

  /*  qDebug() << "nb row" <<  model.rowCount();
    for (int i = 0; i < model.rowCount(); ++i) {
        int id = model.record(i).value("PCF_NAME").toInt();
        QString name = model.record(i).value("PCF_NAME").toString();
        qDebug() << id << name;
    }*/
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
