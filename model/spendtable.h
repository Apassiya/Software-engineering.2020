#ifndef SPENDTABLE_H
#define SPENDTABLE_H

#include "tablemodel.h"


class SpendTable : public TableModel
{
    Q_OBJECT

public:
    explicit SpendTable(QObject *parent = nullptr);

    // Header:
    void setHeader() override;

   // Basic functionality:
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    // Editable:
//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) override;

//    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual bool add(QSqlRecord) override;
    virtual bool edit(QSqlRecord) override;
    virtual bool remove(int id) override;
    virtual void select() override;

    virtual int  sum() override;

    virtual void setFilter(int day, int month, int year) override;

private:
};

#endif // SPENDTABLE_H
