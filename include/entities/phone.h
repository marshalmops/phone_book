#ifndef PHONE_H
#define PHONE_H

#include "ientity.h"

class Phone : public IEntity
{
public:
    Phone();
    Phone(const QString number, const QString type, const quint64 id = 0, const quint64 typeId = 0/*, const quint64 abonentId = 0*/);
    
    virtual bool       initializeWithSqlRecord(const QSqlRecord &record) override;
    virtual QSqlRecord toSqlRecord            ()                   const override;

    quint64 getPhoneId() const;
    QString getNumber () const;
    QString getType   () const;
    quint64 getTypeId () const;
    
    void setPhoneId(const quint64 phoneId);
    void changeData(std::shared_ptr<Phone> newPhoneData);
    
    
private:
    quint64 m_phoneId;
    QString m_number;
    QString m_type;
    quint64 m_typeId;
    //quint64 m_abonentId;
    
    bool m_isPhoneIdSet;
};

#endif // PHONE_H
