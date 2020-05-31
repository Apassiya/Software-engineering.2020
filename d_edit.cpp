#include "d_edit.h"
#include "ui_d_edit.h"

#include <QMessageBox>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QDialog>

R_d_edit::R_d_edit(QSqlDatabase db, QString tableSL, int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::R_d_edit)
{
    ui->setupUi(this);
    QSqlQuery qry(db);
    QString tmp;
    qry.prepare("SELECT день, месяц, год, сумма FROM доход WHERE id = :id;");
    qry.bindValue(":id", id);
    qry.exec();
    qry.next();

    int day = qry.value(0).toInt();
    int month = qry.value(1).toInt();
    int year = qry.value(2).toInt();
    int sum = qry.value(3).toInt();

    ui->spinBox->setValue(day);
    ui->spinBox_2->setValue(month);
    ui->spinBox_3->setValue(year);
    ui->spinBox_4->setValue(sum);

    ui->spinBox->setMaximum(31);
    ui->spinBox_2->setMaximum(12);
    ui->spinBox_3->setMaximum(2020);
}

int R_d_edit::day() {
    ui->spinBox->setMaximum(31);
    return ui->spinBox->value();
}

int R_d_edit::month() {
    ui->spinBox_2->setMaximum(12);
    return ui->spinBox_2->value();
}

int R_d_edit::year() {
    ui->spinBox_3->setMaximum(2020);
    return ui->spinBox_3->value();
}

int R_d_edit::sum() {
    return ui->spinBox_4->value();
}

R_d_edit::~R_d_edit()
{
    delete ui;
}
