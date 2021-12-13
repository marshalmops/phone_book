#ifndef ABONENT_H
#define ABONENT_H

#include "ientity.h"

class Abonent : public IEntity
{
public:
    Abonent();
    Abonent(const QString surname, const QString name, const QString patronymic, const quint64 id = 0);
    
    virtual bool       initializeWithSqlRecord(const QSqlRecord &record) override;
    virtual QSqlRecord toSqlRecord            ()                   const override;

    quint64 getAbonentId () const;
    QString getSurname   () const;
    QString getName      () const;
    QString getPatronymic() const;
    
    void setAbonentId(const quint64 abonentId);
    void changeData  (std::shared_ptr<Abonent> newAbonentData);
    
private:
    bool m_isAbonentIdSet;
    
    quint64 m_abonentId;
    QString m_surname;
    QString m_name;
    QString m_patronymic;
};

#endif // ABONENT_H
