#include "../../../include/database/databaseconnections/databaseconnectionsqlite.h"

DatabaseConnectionSQLite::DatabaseConnectionSQLite()
{
    
}

bool DatabaseConnectionSQLite::prepareDatabaseConnection(QSqlDatabase &db)
{
    db.setDatabaseName(C_DEFAULT_SQLITE_FILENAME);
    
    return true;
}
