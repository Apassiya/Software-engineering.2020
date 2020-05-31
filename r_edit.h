#ifndef R_EDIT_H
#define R_EDIT_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class R_edit;
}

class R_edit : public QDialog
{
    Q_OBJECT

public:
    explicit R_edit(QSqlRecord record, QWidget *parent = nullptr);
    QSqlRecord data();
    ~R_edit();

private slots:
    void on_buttonBox_accepted();

    void on_spinBoxMonth_valueChanged(int arg1);

private:
    Ui::R_edit *ui;
    QSqlRecord data_;
};

#endif // R_EDIT_H
