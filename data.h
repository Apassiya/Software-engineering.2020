#ifndef DATA_H
#define DATA_H

#include <QDialog>

namespace Ui {
class Data;
}

class Data : public QDialog
{
    Q_OBJECT

public:
    explicit Data(QWidget *parent = nullptr);
    ~Data();

private:
    Ui::Data *ui;
};

#endif // DATA_H
