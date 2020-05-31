#include "data_edit.h"
#include "ui_data_edit.h"

data_edit::data_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::data_edit)
{
    ui->setupUi(this);
}

data_edit::~data_edit()
{
    delete ui;
}
