#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sc2kdbmanager.h"
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    SC2KDBManager manager;
    QSignalMapper mapperUpdate;
    QSignalMapper mapperInsert;
    QSignalMapper mapperRevert;
    QHash<QString,QTableView *> hashTbl;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectDB_clicked();

    void on_newparam_clicked();

    void on_getparam_clicked();

    void on_btnNewPCFRec_clicked();

    void on_connectDB_2_clicked();

    void on_pushButton_clicked();

    void insertNewRow(QString table);
    void submitChanges(QString table);
    void revertChanges(QString table);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    void initTabs();
    void deleteTabs();
    void writeLog(QString msg);
};

#endif // MAINWINDOW_H
