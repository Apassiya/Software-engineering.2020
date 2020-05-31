#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QDate>
//#include <QFileDialog>
//#include <QDialog>

#include "model/tablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void connectToSql();
    ~MainWindow();

private slots:
    void on_dohod_triggered();

    void on_rashod_triggered();

    void on_searc_d_clicked();

    void on_searc_r_clicked();

    void on_print_d_clicked();

    void on_print_r_clicked();

    void on_update_clicked();

private:
    void sumUpdate();


    Ui::MainWindow *ui;
//    QSqlDatabase db;
    TableModel *modelIncoming, *modelSpend;
//    QSqlQuery *qry, *qry1, *qry3, *qry4;
//    QString table;
};
#endif // MAINWINDOW_H
