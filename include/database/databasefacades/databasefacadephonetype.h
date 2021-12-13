#ifndef DATABASEFACADEPHONETYPE_H
#define DATABASEFACADEPHONETYPE_H

#include "../../entities/phonetype.h"
#include "../databasemanager.h"

class DatabaseFacadePhoneType
{
public:
    DatabaseFacadePhoneType();
    
    bool selectAllPhoneTypes(QVector<std::shared_ptr<PhoneType>> &phonesTypes);
    bool insertPhoneType    (const std::shared_ptr<PhoneType> phoneTypeData);
    bool updatePhoneType    (std::shared_ptr<PhoneType> phoneData);
    bool deletePhoneType    (const quint64 phoneTypeId);
};

#endif // DATABASEFACADEPHONETYPE_H
