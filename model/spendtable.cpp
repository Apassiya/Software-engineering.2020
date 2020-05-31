#include "spendtable.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtDebug>

#include "db.h"

SpendTable::SpendTable(QObject *parent)
    : TableModel(parent)
{
}

void SpendTable::setHeader()
{
    setHeaderData(0, Qt::Horizontal, tr("Идентификатор"));
    setHeaderData(1, Qt::Horizontal, tr("Сумма"));
    setHeaderData(2, Qt::Horizontal, tr("Дата"));
    setHeaderData(3, Qt::Horizontal, tr("День"));
    setHeaderData(4, Qt::Horizontal, tr("Месяц"));
    setHeaderData(5, Qt::Horizontal, tr("Год"));
}

//QVariant SpendTable::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//bool SpendTable::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}

//int SpendTable::rowCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//int SpendTable::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//QVariant SpendTable::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    QVariant value = QSqlQueryModel::data(index, role);
//        return value;
//}

//bool SpendTable::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags SpendTable::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable; // FIXME: Implement me!
//}

//bool SpendTable::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endInsertRows();
//}

//bool SpendTable::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//}

//bool SpendTable::removeRows(int row, int count, const QModelIndex &parent)
//{
//    beginRemoveRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endRemoveRows();
//}

//bool SpendTable::removeColumns(int column, int count, const QModelIndex &parent)
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endRemoveColumns();
//}

bool SpendTable::add(QSqlRecord record)
{
    QSqlQuery query;

    query.prepare("INSERT INTO расход values (:id, :day, :month, :year, :sum);");

    QSqlQuery qry1;
    qry1.prepare("SELECT max(id) FROM расход");
    qry1.exec();
    qry1.first();
    int count = qry1.value(0).toInt() + 1;

    query.bindValue(":id", count ); //FIXME: Test this!!!
    query.bindValue(":day", record.value("день") );
    query.bindValue(":month", record.value("месяц") );
    query.bindValue(":year", record.value("год") );
    query.bindValue(":sum", record.value("сумма") );

    auto res = query.exec();
    qDebug() << "SpendTable::add error: " << query.lastError();
    return res;
}

bool SpendTable::edit(QSqlRecord record)
{
    QSqlQuery query;

    query.prepare(
                "UPDATE расход "
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
    qDebug() << "SpendTable::edit error: " << query.lastError();
    return res;
}

bool SpendTable::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM расход WHERE id = :id;");

    query.bindValue(":id", record(id).value("id").toInt());

    auto res = query.exec();
    qDebug() << "SpendTable::remove error: " << query.lastError();
    return res;
}

void SpendTable::select()
{
    QString queryStr = "SELECT id, сумма, concat(день, '.' , месяц , '.' , год), "
                       "день, месяц, год "
                       "FROM расход ";

    if(filterState_ && !filter_.isEmpty() ) {
        queryStr += " WHERE " + filter_;
    }
    queryStr += " ;";

    setQuery(queryStr);

    qDebug() << "SpendTable::select error: " << lastError().text();
}

int SpendTable::sum()
{
    QString queryStr = "SELECT SUM(сумма) FROM расход ";

    if(filterState_ && !filter_.isEmpty() ) {
        queryStr += " WHERE " + filter_;
    }
    queryStr += " ;";

    QSqlQuery query;

    query.prepare(queryStr);
    query.exec();
    query.next();

    int sum = query.value(0).toInt();

    return sum;
}

void SpendTable::setFilter(int day, int month, int year)
{
    if(day != 0 || month != 0 || year != 0) {
        filter_ = QString("день = %1 AND месяц = %2 AND год = %3")
                .arg(day)
                .arg(month)
                .arg(year);

        if(day == 0) {
            filter_.remove("день = 0 AND ");
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
