#ifndef PHONETYPE_H
#define PHONETYPE_H

#include "ientity.h"

class PhoneType : public IEntity
{
public:
    PhoneType();
    PhoneType(const QString type, const quint64 phoneTypeId = 0);
    
    virtual bool       initializeWithSqlRecord(const QSqlRecord &record) override;
    virtual QSqlRecord toSqlRecord            ()                   const override;

    quint64 getTypeId() const;
    QString getType  () const;
    
    void setPhoneTypeId(const quint64 phoneTypeId);  
    
    void changeData(std::shared_ptr<PhoneType> newPhoneTypeData);
    
    
private:
    quint64 m_phoneTypeId;
    QString m_type;
    
    bool m_isPhoneTypeIdSet;
};

#endif // PHONETYPE_H
