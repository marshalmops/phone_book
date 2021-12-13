#include "../../../include/database/databaseconnections/databaseconnectiongenerator.h"

std::unique_ptr<IDatabaseConnection> DatabaseConnectionGenerator::generateDatabaseConnectionOfType(QSqlDatabase &db, IDatabaseConnection::Type type)
{
    std::unique_ptr<IDatabaseConnection> dbConnection;
    
    switch (type) {
        case IDatabaseConnection::Type::T_SQLITE: {
            dbConnection = std::make_unique<DatabaseConnectionSQLite>(DatabaseConnectionSQLite());
        
            break;
        }
        default:
            std::unique_ptr<IDatabaseConnection>();
    }
    
    if (!dbConnection->prepareDatabaseConnection(db))
        return std::unique_ptr<IDatabaseConnection>();
    
    return std::move(dbConnection);
}
