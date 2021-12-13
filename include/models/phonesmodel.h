#ifndef PHONESMODEL_H
#define PHONESMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QVector>

#include "../entities/phone.h"

class PhonesModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    enum Field {
        C_ID = 0,
        C_PHONE,
        C_TYPE,
        C_COUNT
    };
    
    explicit PhonesModel(QObject *parent = nullptr);
    
    virtual int         rowCount   (const QModelIndex &parent)                          const override;
    virtual int         columnCount(const QModelIndex &parent)                          const override;
    virtual QVariant    data       (const QModelIndex &index, int role)                 const override;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role) const override;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent)     const override;

    void setData  (const QVector<std::shared_ptr<Phone>> &phones);
    void clearData();
    
    void addPhone   (const std::shared_ptr<Phone> phone);
    void updatePhone(const QModelIndex index, const std::shared_ptr<Phone> newPhoneData);
    void removePhone(const QModelIndex &index);
    
private:
    QVector<std::shared_ptr<Phone>> m_phones;
    
};

#endif // PHONESMODEL_H
