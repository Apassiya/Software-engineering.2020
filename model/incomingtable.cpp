#include "incomingtable.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtDebug>

IncomingTable::IncomingTable(QObject *parent)
    : TableModel(parent)
{
}

void IncomingTable::setHeader()
{
    setHeaderData(0, Qt::Horizontal, tr("Идентификатор"));
    setHeaderData(1, Qt::Horizontal, tr("Сумма"));
    setHeaderData(2, Qt::Horizontal, tr("Дата"));
    setHeaderData(3, Qt::Horizontal, tr("День"));
    setHeaderData(4, Qt::Horizontal, tr("Месяц"));
    setHeaderData(5, Qt::Horizontal, tr("Год"));
}

//QVariant IncomingTable::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    // FIXME: Implement me!
//    return QVariant();
//}

//bool IncomingTable::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags IncomingTable::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable; // FIXME: Implement me!
//}


bool IncomingTable::add(QSqlRecord record)
{
    QSqlQuery query;

    query.prepare("INSERT INTO доход values (:id, :day, :month, :year, :sum)");

    QSqlQuery qry1;
    qry1.prepare("SELECT max(id) FROM доход");
    qry1.exec();
    qry1.first();
    int count = qry1.value(0).toInt() + 1;

    query.bindValue(":id", count);
    query.bindValue(":day", record.value("день") );
    query.bindValue(":month", record.value("месяц") );
    query.bindValue(":year", record.value("год") );
    query.bindValue(":sum", record.value("сумма") );

    auto res = query.exec();
    qDebug() << "IncomingTable::add error: " << query.lastError();
    return res;
}

bool IncomingTable::edit(QSqlRecord record)
{
    QSqlQuery query;

    query.prepare(
                "UPDATE доход "
                "SET день = :day, "
                "месяц = :month, "
                "год = :year, "
                "сумма = :sum "
                "WHERE id = :id;"
                );

    query.bindValue(":id", record.value("id") );
    query.bindValue(":day", record.value("день") );
    query.bindValue(":month", record.value("месяц") );
    query.bindValue(":year", record.value("год") );
    query.bindValue(":sum", record.value("сумма") );

    auto res = query.exec();
    qDebug() << "IncomingTable::add error: " << query.lastError();
    return res;
}

bool IncomingTable::remove(int id)
{
    //TODO: Test implementation
    QSqlQuery query;

    query.prepare("DELETE FROM доход WHERE id = :id ;");

    query.bindValue(":id", record(id).value("id").toInt());

    auto res = query.exec();
    qDebug() << "IncomingTable::add error: " << query.lastError();
    return res;
}

void IncomingTable::select()
{
    QString queryStr = "SELECT id, сумма, concat(день, '.' , месяц , '.' , год), "
                       "день, месяц, год "
                       "FROM доход ";

    if(filterState_ && !filter_.isEmpty() ) {
        queryStr += " WHERE " + filter_;
    }
    queryStr += " ;";

    setQuery(queryStr);

    qDebug() << "IncomingTable::add error: " << lastError().text();
    qDebug() << "IncomingTable::add queryStr: " << queryStr;
}

int IncomingTable::sum()
{
    QString queryStr = "SELECT SUM(сумма) FROM доход ";

    if(filterState_ && !filter_.isEmpty() ) {
        queryStr += " WHERE " + filter_;
    }
    queryStr += " ;";

    QSqlQuery query;

    query.prepare(queryStr);

    int sum = query.value(0).toInt();

    return sum;
}

void IncomingTable::setFilter(int day, int month, int year)
{
    if(day != 0 || month != 0 || year != 0) {
        filter_ = QString("день = %1 AND месяц = %2 AND год = %3")
                .arg(day)
                .arg(month)
                .arg(year);

        if(day == 0) {
            filter_.remove("день = 0 AND");
        }
        if(month == 0) {
            filter_.remove("месяц = 0 AND ");
        }
        if(year == 0) {
            filter_.remove("AND год = 0");
        }
        filterState_ = true;
    } else {
        filterState_ = false;
        filter_.clear();
    }
}
