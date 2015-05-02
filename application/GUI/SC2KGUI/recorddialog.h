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
    QList<QLineEdit *> lineEdits;
public:
    RecordDialog(QString wndName, QSqlRecord record);

private:
    void createField(QSqlField field, QFormLayout *layout);

private slots:
    void createRecord();
};

#endif // RECORDDIALOG_H
