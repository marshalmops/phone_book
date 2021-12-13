#include "../../include/entities/abonent.h"

Abonent::Abonent()
    : m_abonentId     (0),
      m_surname       (QString()),
      m_name          (QString()),
      m_patronymic    (QString()),
      m_isAbonentIdSet(false)
{
    
}

Abonent::Abonent(const QString surname, const QString name, const QString patronymic, const quint64 id)
    : m_abonentId     (id),
      m_surname       (surname),
      m_name          (name),
      m_patronymic    (patronymic)
{
    m_isAbonentIdSet = (m_abonentId == 0 ? false : true);
}

bool Abonent::initializeWithSqlRecord(const QSqlRecord &record)
{
    quint64 id         = record.value("AbonentID").toUInt();
    QString surname    = record.value("Surname").toString();
    QString name       = record.value("Name").toString();
    QString patronymic = record.value("Patronymic").toString();
    
    if (surname.isEmpty()
     || name.isEmpty()
     || patronymic.isEmpty())
    {
        return false;
    }
    
    m_abonentId      = id;
    m_surname        = surname;
    m_name           = name;
    m_patronymic     = patronymic;
    m_isAbonentIdSet = true;
    
    return true;
}

QSqlRecord Abonent::toSqlRecord() const
{
    QSqlRecord sqlRecord{};
    
    sqlRecord.append(QSqlField("AbonentID"));
    sqlRecord.append(QSqlField("Surname"));
    sqlRecord.append(QSqlField("Name"));
    sqlRecord.append(QSqlField("Patronymic"));
    
    sqlRecord.setValue("AbonentID",  m_abonentId);
    sqlRecord.setValue("Surname",    m_surname);
    sqlRecord.setValue("Name",       m_name);
    sqlRecord.setValue("Patronymic", m_patronymic);
    
    return sqlRecord;
}

quint64 Abonent::getAbonentId() const
{
    return m_abonentId;
}

QString Abonent::getSurname() const
{
    return m_surname;
}

QString Abonent::getName() const
{
    return m_name;
}

QString Abonent::getPatronymic() const
{
    return m_patronymic;
}

void Abonent::setAbonentId(const quint64 abonentId)
{
    if (m_isAbonentIdSet)
        return;
    
    m_abonentId      = abonentId;
    m_isAbonentIdSet = true;
}

void Abonent::changeData(std::shared_ptr<Abonent> newAbonentData)
{
    if (newAbonentData->getSurname().isEmpty() 
     || newAbonentData->getName().isEmpty() 
     || newAbonentData->getPatronymic().isEmpty())
    {
        return;
    }
    
    m_surname    = newAbonentData->m_surname;
    m_name       = newAbonentData->m_name;
    m_patronymic = newAbonentData->m_patronymic;
}
