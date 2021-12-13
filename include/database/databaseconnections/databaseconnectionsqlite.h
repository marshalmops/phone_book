#ifndef DATABASECONNECTIONSQLITE_H
#define DATABASECONNECTIONSQLITE_H

#include "idatabaseconnection.h"

class DatabaseConnectionSQLite : public IDatabaseConnection
{
    constexpr static const char* C_DEFAULT_SQLITE_FILENAME = "phonebook.db";
    
public:
    DatabaseConnectionSQLite();
    
    virtual bool prepareDatabaseConnection(QSqlDatabase &db) override;
};

#endif // DATABASECONNECTIONSQLITE_H
