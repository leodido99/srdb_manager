#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sc2kdbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    SC2KDBManager manager;

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

private:
    Ui::MainWindow *ui;
    void initTabs();
};

#endif // MAINWINDOW_H
