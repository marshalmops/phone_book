#include "../../include/entities/phone.h"

Phone::Phone()
    : m_phoneId     (0),
      m_number      (QString()),
      m_type        (QString()),
      m_typeId      (0),
      m_isPhoneIdSet(false)
      //m_abonentId(0)
{
    
}

Phone::Phone(const QString number, const QString type, const quint64 id/*, const quint64 abonentId*/, const quint64 typeId)
    : m_phoneId  (id),
      m_number   (number),
      m_type     (type),
      m_typeId   (typeId)
      //m_abonentId(abonentId)
{
    m_isPhoneIdSet = (id == 0 ? false : true);
}

bool Phone::initializeWithSqlRecord(const QSqlRecord &record)
{
    quint64 id        = record.value("PhoneID").toUInt();
    QString number    = record.value("Phone").toString();
    QString type      = record.value("Type").toString();
    quint64 typeId    = record.value("PhoneTypeID").toUInt();
    //quint64 abonentId = record.value("AbonentID").toUInt();
    
    if (number.isEmpty()
     || type.isEmpty())
    {
        return false;
    }
    
    m_phoneId      = id;
    m_number       = number;
    m_type         = type;
    m_typeId       = typeId;
    m_isPhoneIdSet = true;
    //m_abonentId = abonentId;
    
    return true;
}

QSqlRecord Phone::toSqlRecord() const
{
    QSqlRecord sqlRecord{};
    
    sqlRecord.append(QSqlField("PhoneID"));
    sqlRecord.append(QSqlField("Phone"));
    sqlRecord.append(QSqlField("Type"));
    sqlRecord.append(QSqlField("PhoneTypeID"));
    //sqlRecord.append(QSqlField("AbonentID"));
    
    sqlRecord.setValue("PhoneID",     m_phoneId);
    sqlRecord.setValue("Phone",       m_number);
    sqlRecord.setValue("Type",        m_type);
    sqlRecord.setValue("PhoneTypeID", m_typeId);
    //sqlRecord.setValue("AbonentID", m_abonentId);
    
    return sqlRecord;
}

quint64 Phone::getPhoneId() const
{
    return m_phoneId;
}

QString Phone::getNumber() const
{
    return m_number;
}

QString Phone::getType() const
{
    return m_type;
}

quint64 Phone::getTypeId() const
{
    return m_typeId;
}

void Phone::setPhoneId(const quint64 phoneId)
{
    if (m_isPhoneIdSet)
        return;
    
    m_phoneId      = phoneId;
    m_isPhoneIdSet = true;
}

void Phone::changeData(std::shared_ptr<Phone> newPhoneData)
{
    if (newPhoneData->getType().isEmpty() 
     || newPhoneData->getNumber().isEmpty() 
     || (newPhoneData->getTypeId() == 0))
    {
        return;
    }
    
    m_number = newPhoneData->m_number;
    m_type   = newPhoneData->m_type;
    m_typeId = newPhoneData->m_typeId;
}
