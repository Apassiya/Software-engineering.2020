#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

void TableModel::setHeader()
{

}

void TableModel::setFilter(QString filter)
{
    filter_ = filter;
}
