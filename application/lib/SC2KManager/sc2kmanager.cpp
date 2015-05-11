#include "sc2kmanager.h"

#include <QDebug>

#include <QSql>

SC2KManager::SC2KManager()
{
    qDebug() << "SC2KManager lib loaded";
}

bool SC2KManager::connect(QString host, QString userName, QString password, QString databaseName)
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);
    return db.open();
}
