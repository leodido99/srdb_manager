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
public:
    RecordDialog(QString wndName, QSqlRecord record);
    void setNbFieldsPerRow(int nbfield);

private:
    void createField(QSqlField field, QFormLayout *layout);

private slots:
    void createRecord();

    /*!
     * \brief Triggered when an edit field is finished being edited
     * \param fieldname Then name of the field to update
     * Links the edit field to the SQL record field
     */
    void updateRecord(QString fieldname);

    void updateFields();
};

#endif // RECORDDIALOG_H
