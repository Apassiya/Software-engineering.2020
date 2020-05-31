#include "r_edit.h"
#include "ui_r_edit.h"

#include <QMessageBox>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QDialog>

R_edit::R_edit(QSqlRecord record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::R_edit),
    data_(record)
{
    ui->setupUi(this);

    int day = data_.value("день").toInt();
    int month = data_.value("месяц").toInt();
    int year = data_.value("год").toInt();
    QString sum = data_.value("сумма").toString();

    ui->spinBoxDay->setValue(day);
    ui->spinBoxMonth->setValue(month);
    ui->spinBoxYear->setValue(year);
    ui->lineEdit->setText(sum);
}

QSqlRecord R_edit::data() {
    return data_;
}


R_edit::~R_edit()
{
    delete ui;
}

void R_edit::on_buttonBox_accepted()
{
    data_.setValue("день", ui->spinBoxDay->value());
    data_.setValue("месяц", ui->spinBoxMonth->value());
    data_.setValue("год", ui->spinBoxYear->value());
    data_.setValue("сумма", ui->lineEdit->text());
}

void R_edit::on_spinBoxMonth_valueChanged(int arg1)
{
    switch (arg1) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        ui->spinBoxDay->setMaximum(31);
        break;

    case 2:
        if(ui->spinBoxYear->value() % 4 == 0) {
            ui->spinBoxDay->setMaximum(29);
        } else {
            ui->spinBoxDay->setMaximum(28);
        }
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        ui->spinBoxDay->setMaximum(30);
        break;
    }
}
