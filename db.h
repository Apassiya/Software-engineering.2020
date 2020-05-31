#ifndef DB_H
#define DB_H


#include <QSqlDatabase>

class DB {
public:
    DB();
    ~DB();

    static bool conection();
    static bool reconection();
    static bool disconection();

    static QSqlDatabase& db();

private:
    static QSqlDatabase *db_;
};

#endif // DB_H
