#ifndef IDATABASECONNECTION_H
#define IDATABASECONNECTION_H

#include <QSqlDatabase>
#include <QHash>

class IDatabaseConnection {
public:
    enum Type : quint8 {
        T_SQLITE = 0,
        T_COUNT
    };
    
    static const QString getStringType(const Type type) {
        if (type >= Type::T_COUNT)
            return QString();
        
        static const QHash<Type, QString> typeHash = {
            {Type::T_SQLITE, "QSQLITE"}  
        };
        
        return typeHash[type];
    }
    
    virtual ~IDatabaseConnection() = default;
    
    virtual bool prepareDatabaseConnection(QSqlDatabase &db) = 0;
};

#endif // IDATABASECONNECTION_H
