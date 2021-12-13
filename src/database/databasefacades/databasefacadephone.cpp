#include "../../../include/database/databasefacades/databasefacadephone.h"

DatabaseFacadePhone::DatabaseFacadePhone()
{
    
}

bool DatabaseFacadePhone::selectAllPhonesOfAbonent(QVector<std::shared_ptr<Phone> > &phones, const QString &abonentId)
{
    QSqlQuery query{};
    
    if ((query = DatabaseManager::selectExec({"*"},
                                             {"Phone", "PhoneType"},
                                             "AbonentId = " + abonentId + " AND Phone.PhoneTypeID = PhoneType.PhoneTypeID")).lastError().isValid())
    {
        return false;
    }
    
    while (query.next()) {
        std::shared_ptr<Phone> newPhone = std::make_shared<Phone>(Phone());
        
        newPhone->initializeWithSqlRecord(query.record());
        
        phones += std::shared_ptr<Phone>(newPhone);
    }
    
    return true;
}

bool DatabaseFacadePhone::insertPhoneToAbonent(const std::shared_ptr<Phone> phoneData, const quint64 abonentId)
{
    QStringList inserts{};
    
    inserts << phoneData->getNumber();
    inserts << QString::number(phoneData->getTypeId());
    inserts << QString::number(abonentId);
    
    if (!DatabaseManager::insertExec(inserts, "Phone(Phone, PhoneTypeID, AbonentID)"))
        return false;
    
    QSqlQuery phoneId = DatabaseManager::selectExec({"MAX(PhoneID)"}, {"Phone"}, QString("Phone = \"%1\" AND PhoneTypeID = \"%2\"").arg(phoneData->getNumber()).arg(phoneData->getTypeId()));
    
    if (!phoneId.next())
        return false;
    
    bool convCheck{false};
    
    phoneData->setPhoneId(phoneId.value(0).toUInt(&convCheck));

    return convCheck;
}

bool DatabaseFacadePhone::updatePhone(std::shared_ptr<Phone> phoneData)
{
    QStringList setters{};
    
    setters << "Phone = \""       + phoneData->getNumber()                  + '\"';
    setters << "PhoneTypeID = \"" + QString::number(phoneData->getTypeId()) + '\"';
    
    return DatabaseManager::updateExec(setters, {"Phone"}, "PhoneID = " + QString::number(phoneData->getPhoneId()));
}

bool DatabaseFacadePhone::deletePhoneById(const quint64 phoneId)
{
    return DatabaseManager::deleteExec("Phone", "PhoneID = " + QString::number(phoneId));
}
