#include "r_d.h"
#include "d_edit.h"
#include "r_edit.h"
#include "ui_r_d.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDialog>
#include <QMessageBox>
#include <QSqlError>

#include <QSqlRecord>

R_d::R_d(TableModel *model, QString title,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::R_d)
{
    ui->setupUi(this);

    this->model_ = model;
    model_->select();
    model_->setHeader();


    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(3, true);
    ui->tableView->setColumnHidden(4, true);
    ui->tableView->setColumnHidden(5, true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->setWindowTitle(title);

    //TODO: навести красоту!
}

R_d::~R_d()
{
    delete ui;
}

void R_d::on_add_clicked()
{
    R_edit *dialog = new R_edit(model_->record(), this);
    if(dialog->exec() == QDialog::Accepted) {
        model_->add(dialog->data());
        model_->select();
    }
}

void R_d::on_edit_clicked()
{
    R_edit *editDialog = new R_edit(model_->record(ui->tableView->currentIndex().row()), this);
    if(editDialog->exec() == QDialog::Accepted) {
        model_->edit(editDialog->data());
        model_->select();
    }
}

void R_d::on_delete_2_clicked()
{
    auto bYes = QMessageBox::question(this, "Удаление записи.","Вы желаете удалить запись?",
                                 QMessageBox::Yes|QMessageBox::No);

    if(bYes == QMessageBox::Yes) {
        model_->remove(ui->tableView->currentIndex().row());
        model_->select();
    }
}
