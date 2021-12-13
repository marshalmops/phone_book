#include "../../../include/database/databasefacades/databasefacadephonetype.h"

DatabaseFacadePhoneType::DatabaseFacadePhoneType()
{
    
}

bool DatabaseFacadePhoneType::selectAllPhoneTypes(QVector<std::shared_ptr<PhoneType> > &phonesTypes)
{
    QSqlQuery query{};
    
    if ((query = DatabaseManager::selectExec({"*"}, {"PhoneType"})).lastError().isValid())
        return false;
    
    while (query.next()) {
        std::shared_ptr<PhoneType> newPhoneType = std::make_shared<PhoneType>(PhoneType());
        
        newPhoneType->initializeWithSqlRecord(query.record());
        
        phonesTypes += std::shared_ptr<PhoneType>(newPhoneType);
    }
    
    return true;
}

bool DatabaseFacadePhoneType::insertPhoneType(const std::shared_ptr<PhoneType> phoneTypeData)
{
    QStringList inserts{};
    
    inserts << phoneTypeData->getType();
    
    if (!DatabaseManager::insertExec(inserts, "PhoneType(Type)"))
        return false;
    
    QSqlQuery phoneTypeId = DatabaseManager::selectExec({"MAX(PhoneTypeID)"}, {"PhoneType"}, QString("Type = \"%1\"").arg(phoneTypeData->getType()));
    
    if (!phoneTypeId.next())
        return false;
    
    bool convCheck{false};
    
    phoneTypeData->setPhoneTypeId(phoneTypeId.value(0).toUInt(&convCheck));

    return convCheck;
}

bool DatabaseFacadePhoneType::updatePhoneType(std::shared_ptr<PhoneType> phoneTypeData)
{
    QStringList setters{};
    
    setters << "Type = \"" + phoneTypeData->getType() + '\"';
    
    return DatabaseManager::updateExec(setters, {"PhoneType"}, "PhoneTypeID = " + QString::number(phoneTypeData->getTypeId()));
}

bool DatabaseFacadePhoneType::deletePhoneType(const quint64 phoneTypeId)
{
    return DatabaseManager::deleteExec("PhoneType", "PhoneTypeID = " + QString::number(phoneTypeId));    
}
