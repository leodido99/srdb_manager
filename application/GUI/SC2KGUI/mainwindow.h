#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectDB_clicked();

    void on_newparam_clicked();

    void on_getparam_clicked();

    void on_btnNewPCFRec_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
