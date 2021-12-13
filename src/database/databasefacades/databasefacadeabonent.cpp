#include "../../../include/database/databasefacades/databasefacadeabonent.h"

DatabaseFacadeAbonent::DatabaseFacadeAbonent()
{
    
}

bool DatabaseFacadeAbonent::insertAbonent(const std::shared_ptr<Abonent> abonentData)
{
    QStringList inserts{};
    
    inserts << abonentData->getSurname();
    inserts << abonentData->getName();
    inserts << abonentData->getPatronymic();
    
    if (!DatabaseManager::insertExec(inserts, "Abonent(Surname, Name, Patronymic)"))
        return false;
    
    QSqlQuery abonentId = DatabaseManager::selectExec({"MAX(AbonentID)"}, {"Abonent"}, QString("Surname = \"%1\" AND Name = \"%2\" AND Patronymic = \"%3\"").arg(abonentData->getSurname(),abonentData->getName(), abonentData->getPatronymic()));
    
    if (!abonentId.next())
        return false;
    
    bool convCheck{false};
    
    abonentData->setAbonentId(abonentId.value(0).toUInt(&convCheck));

    return convCheck;
}

bool DatabaseFacadeAbonent::selectAllAbonents(QVector<std::shared_ptr<Abonent> > &abonents)
{
    QSqlQuery query{};
    
    if ((query = DatabaseManager::selectExec({"*"}, {"Abonent"})).lastError().isValid())
        return false;
    
    while (query.next()) {
        std::shared_ptr<Abonent> newAbonent = std::make_shared<Abonent>(Abonent());
        
        newAbonent->initializeWithSqlRecord(query.record());
        
        abonents += std::shared_ptr<Abonent>(newAbonent);
    }
    
    return true;
}

bool DatabaseFacadeAbonent::updateAbonent(std::shared_ptr<Abonent> abonentData)
{
    QStringList setters{};
    
    setters << "Surname = \""    + abonentData->getSurname()    + '\"';
    setters << "Name = \""       + abonentData->getName()       + '\"';
    setters << "Patronymic = \"" + abonentData->getPatronymic() + '\"';
    
    return DatabaseManager::updateExec(setters, {"Abonent"}, "AbonentID = " + QString::number(abonentData->getAbonentId()));
}

bool DatabaseFacadeAbonent::deleteAbonentById(const quint64 abonentId)
{
    return DatabaseManager::deleteExec("Abonent", "AbonentID = " + QString::number(abonentId));
}
