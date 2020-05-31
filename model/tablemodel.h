#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlQueryModel>

class TableModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    virtual void setHeader();

    virtual bool add(QSqlRecord) = 0;
    virtual bool edit(QSqlRecord) = 0;
    virtual bool remove(int id) = 0;
    virtual void select() = 0;

    virtual int  sum() = 0;

    virtual void setFilter(QString);
    virtual void setFilter(int day, int month, int year) = 0;

protected:
    QString filter_;
    bool filterState_;

private:

};

#endif // TABLEMODEL_H
