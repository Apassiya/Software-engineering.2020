#include "db.h"

QSqlDatabase* DB::db_;

DB::DB()
{ }

DB::~DB()
{}

bool DB::conection() {
    db_ = new QSqlDatabase;
    *db_ = QSqlDatabase::addDatabase("QPSQL");
    db_->setHostName("localhost");
    db_->setDatabaseName("KurdovayaPRINJ");
    db_->setUserName("postgres");
    db_->setPassword("633307");
    db_->setPort(3307);

    return db_->open();
}

bool DB::reconection() {
    db_->close();
    db_->setHostName("localhost");
    db_->setDatabaseName("KurdovayaPRINJ");
    db_->setUserName("postgres");
    db_->setPassword("633307");
    db_->setPort(3307);

    return db_->open();
}

bool DB::disconection() {
    db_->close();
    return true;
}

QSqlDatabase &DB::db() {
    return *db_;
}
