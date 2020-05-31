#ifndef R_D_H
#define R_D_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDialog>

#include "model/tablemodel.h"

namespace Ui {
class R_d;
}

class R_d : public QDialog
{
    Q_OBJECT

public:
    explicit R_d(TableModel *model_, QString title, QWidget *parent = nullptr);
    ~R_d();

private slots:
    void on_add_clicked();

    void on_edit_clicked();

    void on_delete_2_clicked();

private:
    Ui::R_d *ui;

    TableModel *model_, *model1;
};

#endif // R_D_H
