#ifndef SC2KMANAGER_H
#define SC2KMANAGER_H

#include "sc2kmanager_global.h"
#include <QString>
#include <QSqlDatabase>

class SC2KMANAGERSHARED_EXPORT SC2KManager
{
    QSqlDatabase db;
public:
    SC2KManager();
    bool connect(QString host, QString userName, QString password, QString databaseName);
};

#endif // SC2KMANAGER_H
