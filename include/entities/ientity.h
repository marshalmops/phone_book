#ifndef IENTITY_H
#define IENTITY_H

#include <QSqlRecord>
#include <QHash>
#include <QVariant>
#include <QSqlField>

class IEntity {
public:
    virtual ~IEntity() = default;
    
    virtual bool       initializeWithSqlRecord(const QSqlRecord &record) = 0;
    virtual QSqlRecord toSqlRecord            ()                   const = 0;
};

#endif // IENTITY_H
