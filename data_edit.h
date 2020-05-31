#ifndef DATA_EDIT_H
#define DATA_EDIT_H

#include <QDialog>

namespace Ui {
class data_edit;
}

class data_edit : public QDialog
{
    Q_OBJECT

public:
    explicit data_edit(QWidget *parent = nullptr);
    ~data_edit();

private:
    Ui::data_edit *ui;
};

#endif // DATA_EDIT_H
