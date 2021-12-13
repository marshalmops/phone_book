#ifndef PHONESTYPESMODEL_H
#define PHONESTYPESMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "../entities/phonetype.h"

class PhonesTypesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PhonesTypesModel(const QVector<std::shared_ptr<PhoneType>> &phonesTypes, QObject *parent = nullptr);
    
    virtual QModelIndex index   (int row, int column, const QModelIndex &parent) const override;
    virtual int         rowCount(const QModelIndex &parent)                      const override;
    virtual QVariant    data    (const QModelIndex &index, int role)             const override;
    
    quint64 getPhoneTypeIdByRow    (const int row) const;
    QString getPhoneTypeStringByRow(const int row) const;
    
    int getRowByPhoneType(const quint64 phoneType) const;
    
    void addPhoneType   (const std::shared_ptr<PhoneType> phoneType);
    void updatePhoneType(const QModelIndex index, const std::shared_ptr<PhoneType> newPhoneTypeData);
    void removePhoneType(const QModelIndex &index);  
    
private:
    void initializeModel(const QVector<std::shared_ptr<PhoneType>> &phonesTypes);
    
    QVector<std::shared_ptr<PhoneType>> m_phonesTypes;
};

#endif // PHONESTYPESMODEL_H
