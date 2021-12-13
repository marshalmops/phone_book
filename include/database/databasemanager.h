#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QVector>
#include <QSqlQuery>
#include <QSqlError>

#include "databaseconnections/databaseconnectiongenerator.h"
#include "../entities/ientity.h"

class DatabaseManager
{
public:
    DatabaseManager() = delete;
    
    static bool initializeDatabaseConnection(IDatabaseConnection::Type type = IDatabaseConnection::Type::T_SQLITE);
    
    static QSqlQuery selectExec(const QStringList &attributes, const QStringList &tables, const QString &condition = QString());
    static bool      deleteExec(const QString &table, const QString &condition = QString());
    static bool      insertExec(const QStringList &attributes, const QString &table);
    static bool      updateExec(const QStringList &attributes, const QStringList &tables, const QString &condition = QString());
    
private:
    static bool isConnected();
    
    static std::unique_ptr<IDatabaseConnection> s_dbConnection;
};

#endif // DATABASEMANAGER_H
