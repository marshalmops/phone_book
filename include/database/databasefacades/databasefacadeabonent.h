#ifndef DATABASEFACADEABONENT_H
#define DATABASEFACADEABONENT_H

#include "../../entities/abonent.h"
#include "../databasemanager.h"

class DatabaseFacadeAbonent
{
public:
    DatabaseFacadeAbonent();
    
    bool insertAbonent    (const std::shared_ptr<Abonent> abonentData);
    bool selectAllAbonents(QVector<std::shared_ptr<Abonent>> &abonents);
    bool updateAbonent    (std::shared_ptr<Abonent> abonentData);
    bool deleteAbonentById(const quint64 abonentId);

};

#endif // DATABASEFACADEABONENT_H
