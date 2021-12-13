#include "../../include/entities/phonetype.h"

PhoneType::PhoneType()
    : m_phoneTypeId     (0),
      m_type            (QString()),
      m_isPhoneTypeIdSet(false)
{
    
}

PhoneType::PhoneType(const QString type, const quint64 phoneTypeId)
    : m_phoneTypeId(phoneTypeId),
      m_type       (type)
{
    m_isPhoneTypeIdSet = (phoneTypeId == 0 ? false : true);
}

bool PhoneType::initializeWithSqlRecord(const QSqlRecord &record)
{
    quint64 phoneTypeId = record.value("PhoneTypeID").toUInt();
    QString type        = record.value("Type").toString();
    
    if (type.isEmpty())
        return false;
    
    m_phoneTypeId      = phoneTypeId;
    m_type             = type;
    m_isPhoneTypeIdSet = true;
    
    return true;
}

QSqlRecord PhoneType::toSqlRecord() const
{
    QSqlRecord sqlRecord{};
    
    sqlRecord.append(QSqlField("PhoneTypeID"));
    sqlRecord.append(QSqlField("Type"));
    
    sqlRecord.setValue("PhoneTypeID", m_phoneTypeId);
    sqlRecord.setValue("Type",        m_type);
    
    return sqlRecord;
}

quint64 PhoneType::getTypeId() const
{
    return m_phoneTypeId;
}

QString PhoneType::getType() const
{
    return m_type;
}

void PhoneType::setPhoneTypeId(const quint64 phoneTypeId)
{
    if (m_isPhoneTypeIdSet)
        return;
    
    m_phoneTypeId      = phoneTypeId;
    m_isPhoneTypeIdSet = true;
}

void PhoneType::changeData(std::shared_ptr<PhoneType> newPhoneTypeData)
{
    if (newPhoneTypeData->getType().isEmpty())
        return;
    
    m_type = newPhoneTypeData->m_type;
}
