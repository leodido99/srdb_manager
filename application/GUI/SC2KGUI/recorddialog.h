#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QtWidgets>
#include <QSqlRecord>
#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class RecordDialog : public QDialog
{
    Q_OBJECT
    int nbFieldsPerRow;
    QSqlRecord record;
    QSignalMapper mapper;
    QHash<QString,QLineEdit*> hash;
public:
    RecordDialog(QString wndName, QSqlRecord record);
    void setNbFieldsPerRow(int nbfield);

private:
    //void createField(QSqlField field, QFormLayout *layout);
    void createField(QSqlField field, QHBoxLayout *layout);
    void updateFields();

private slots:
    void createRecord();

    /*!
     * \brief Triggered when an edit field is finished being edited
     * \param fieldname The name of the field to update
     * Links the edit field to the SQL record field
     */
    void updateRecord(QString fieldname);

signals:
    void recordUpdated(QSqlRecord record);
};

#endif // RECORDDIALOG_H
