#ifndef R_D_EDIT_H
#define R_D_EDIT_H


#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDialog>

namespace Ui {
class R_d_edit;
}

class R_d_edit : public QDialog
{
    Q_OBJECT

public:
    explicit R_d_edit(QSqlDatabase db, QString tableSL, int id, QWidget *parent = nullptr);
    int id();
    int day();
    int month();
    int year();
    int sum();
    ~R_d_edit();

private:
    Ui::R_d_edit *ui;
    QSqlQuery *qry;
    QSqlQueryModel *model;
    QString table;
    QSqlDatabase db;
};

#endif // R_D_EDIT_H
