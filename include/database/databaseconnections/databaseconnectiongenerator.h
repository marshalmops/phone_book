#ifndef DATABASECONNECTIONGENERATOR_H
#define DATABASECONNECTIONGENERATOR_H

#include "idatabaseconnection.h"
#include "databaseconnectionsqlite.h"

class DatabaseConnectionGenerator
{
public:
    DatabaseConnectionGenerator() = delete;
    
    static std::unique_ptr<IDatabaseConnection> generateDatabaseConnectionOfType(QSqlDatabase &db, IDatabaseConnection::Type type);
};

#endif // DATABASECONNECTIONGENERATOR_H
