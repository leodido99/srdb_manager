#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sc2kdbmanager.h"
#include "puslist.h"
#include "packetwidget.h"
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
    PUSlist *puslist;
    PacketWidget *packetwidget;
    QTabWidget *sc2k;

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
    void initTabs(QTabWidget *tabWidget);
    void deleteTabs(QTabWidget *tabWidget);
    void writeLog(QString msg);
    void setupWidgets();
};

#endif // MAINWINDOW_H
