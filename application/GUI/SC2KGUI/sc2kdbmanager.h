#ifndef SC2KDBMANAGER_H
#define SC2KDBMANAGER_H

#include <QString>
#include <QtSql>
#include <QListWidget>

typedef struct{

    QString name;               /* Parameter name (mandatory) */
    QString description;        /* Parameter Description */
    QString paramId;            /* On-board ID of the telemetry parameter. */
    QString unit;               /* Unit of the parameter */
    QString paramTypeCode;      /* Parameter Type Code defined by SCOS2000 see xxx (mandatory) */
    QString paramFormatCode;    /* Parameter Format Code defined by SCOS2000 see xxx (mandatory) */
    QString width;
    QString valid;
    QString relatedParam;
    QString category;           /* Parameter category N/S/T (mandatory) */
    QString nature;             /* Nature of the parameter R/D/P/H/S/C (mandatory) */
    QString calibCurve;
    QString inter;
    QString uscon;
    QString decim;
    QString paramVal;
    QString subsys;
    QString rawVal;
    QString sptype;
    QString correlated;
    QString obtid;
    QString darc;
    QString endian;
}scPCF;

typedef enum {
    PCF
}scTables;

class SC2KDBManager
{
    QSqlDatabase db;
    QSqlTableModel *PCFModel;
    QListWidget *log;

public:
    SC2KDBManager();

    /*!
     * \brief Connect to the database
     * \param host
     * \param userName
     * \param password
     * \param databaseName
     * \return
     */
    bool connect(QString host, QString userName, QString password, QString databaseName);

    int getNbTables();


    /*!
     * \brief Create a new monitoring parameter (PCF)
     * \param data
     * \return
     */
    bool newParameter(scPCF data);

    long getNbParameters();

    void getParameters();

    void setLogListView(QListWidget *log);

    QSqlRecord getSQLRecord(scTables table);

    /*!
     * \brief Get the PCF table model
     * Returns a QSqlTableModel of the PCF table to display content
     * \return
     */
    QSqlTableModel *getPCFModel();

    /*!
     * \brief Close the connection with the database
     */
    void close(void);

private:
    bool checkPCFMandatory(scPCF data);
    void init();
    void writeLog(QString msg);
};

#endif // SC2KDBMANAGER_H
