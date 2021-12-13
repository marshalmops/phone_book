#include "../../include/database/databasemanager.h"

std::unique_ptr<IDatabaseConnection> DatabaseManager::s_dbConnection = std::unique_ptr<IDatabaseConnection>();

bool DatabaseManager::initializeDatabaseConnection(IDatabaseConnection::Type type)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(IDatabaseConnection::getStringType(type));
    
    s_dbConnection = DatabaseConnectionGenerator::generateDatabaseConnectionOfType(db, type);
    
    return db.open();
}

QSqlQuery DatabaseManager::selectExec(const QStringList &attributes, const QStringList &tables, const QString &condition)
{
    if (!isConnected())
        return QSqlQuery();
    
    QString queryString{};
    
    queryString += "SELECT ";
    
    for (int i = 0; i < attributes.length(); ++i) {
        queryString += (attributes[i] + (i + 1 == attributes.length() ? "" : ","));
    }
    
    queryString += " FROM ";
    
    for (int i = 0; i < tables.length(); ++i) {
        queryString += (tables[i] + (i + 1 == tables.length() ? "" : ","));
    }
    
    queryString += (condition.isEmpty() ? ";" : QString(" WHERE ") + condition + ";");
    
    return QSqlDatabase::database().exec(queryString);
}

bool DatabaseManager::deleteExec(const QString &table, const QString &condition)
{
    if (!isConnected())
        return false;
    
    QString queryString{};
    
    queryString += "DELETE FROM ";
    queryString += table;
    queryString += " WHERE ";
    queryString += condition;
    queryString += ";";
    
    return !QSqlDatabase::database().exec(queryString).lastError().isValid();
}

bool DatabaseManager::insertExec(const QStringList &attributes, const QString &table)
{
    if (!isConnected())
        return false;
    
    QString queryString{};
    
    queryString += "INSERT INTO ";
    queryString += table;
    queryString += " VALUES(";
    
    for (int i = 0; i < attributes.length(); ++i) {
        queryString += (('\"' + attributes[i] + '\"') + (i + 1 == attributes.length() ? "" : ","));
    }
    
    queryString += ");";
    
    return !QSqlDatabase::database().exec(queryString).lastError().isValid();
}

bool DatabaseManager::updateExec(const QStringList &attributes, const QStringList &tables, const QString &condition)
{
    if (!isConnected())
        return false;
    
    QString queryString{};
    
    queryString += "UPDATE ";
    
    for (int i = 0; i < tables.length(); ++i) {
        queryString += (tables[i] + (i + 1 == tables.length() ? "" : ","));
    }
    
    queryString += " SET ";
    
    for (int i = 0; i < attributes.length(); ++i) {
        queryString += (attributes[i] + (i + 1 == attributes.length() ? "" : ","));
    }
    
    queryString += (condition.isEmpty() ? ";" : QString(" WHERE ") + condition + ";");
    
    return !QSqlDatabase::database().exec(queryString).lastError().isValid();
}

bool DatabaseManager::isConnected()
{
    return s_dbConnection.get() != nullptr;
}
