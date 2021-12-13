#ifndef DATABASEFACADEPHONE_H
#define DATABASEFACADEPHONE_H

#include "../../entities/phone.h"
#include "../databasemanager.h"

class DatabaseFacadePhone
{
public:
    DatabaseFacadePhone();
    
    bool selectAllPhonesOfAbonent(QVector<std::shared_ptr<Phone>> &phones, const QString &abonentId);
    bool insertPhoneToAbonent    (const std::shared_ptr<Phone> phoneData, const quint64 abonentId);
    bool updatePhone             (std::shared_ptr<Phone> phoneData);
    bool deletePhoneById         (const quint64 phoneId);
};

#endif // DATABASEFACADEPHONE_H
