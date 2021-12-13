#include "../../include/models/phonestypesmodel.h"

PhonesTypesModel::PhonesTypesModel(const QVector<std::shared_ptr<PhoneType>> &phonesTypes, QObject *parent)
    : QAbstractListModel(parent)
{
    initializeModel(phonesTypes);
}

QModelIndex PhonesTypesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row >= m_phonesTypes.length() || column > 0)
        return QModelIndex();
    
    return createIndex(row, 0, m_phonesTypes[row].get());
}

int PhonesTypesModel::rowCount(const QModelIndex &parent) const
{
    return m_phonesTypes.length();
}

QVariant PhonesTypesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    
    if (index.row() >= m_phonesTypes.length())
        return QVariant();
    
    return m_phonesTypes[index.row()]->getType();
}

QString PhonesTypesModel::getPhoneTypeStringByRow(const int row) const
{
    if (row >= m_phonesTypes.length())
        return 0;
    
    return m_phonesTypes[row]->getType();
}

int PhonesTypesModel::getRowByPhoneType(const quint64 phoneType) const
{
    if (phoneType == 0)
        return 0;
    
    for (int i = 0; i < m_phonesTypes.length(); ++i) {
        if (m_phonesTypes[i]->getTypeId() == phoneType)
            return i;
    }
    
    return 0;
}

void PhonesTypesModel::addPhoneType(const std::shared_ptr<PhoneType> phoneType)
{
    auto phonesTypesCount = m_phonesTypes.length();
    
    beginInsertRows(QModelIndex(), phonesTypesCount, phonesTypesCount);
    
    m_phonesTypes.push_back(phoneType);
    
    endInsertRows();
}

void PhonesTypesModel::updatePhoneType(const QModelIndex index, const std::shared_ptr<PhoneType> newPhoneTypeData)
{
    if (!index.isValid())
        return;
    
    m_phonesTypes[index.row()]->changeData(newPhoneTypeData);
    
    emit dataChanged(index, index);
}

void PhonesTypesModel::removePhoneType(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    
    PhoneType *phoneType = static_cast<PhoneType*>(index.internalPointer());
    
    if (!phoneType)
        return;
    
    int phoneTypeIndex{-1};
    
    for (int i = 0; i < m_phonesTypes.length(); ++i) {
        if (m_phonesTypes[i]->getTypeId() == phoneType->getTypeId()) {
            phoneTypeIndex = i;
            
            break;
        }
    }
    
    if (phoneTypeIndex < 0)
        return;
    
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    
    m_phonesTypes.removeAt(phoneTypeIndex);
    
    endRemoveRows();
}

void PhonesTypesModel::initializeModel(const QVector<std::shared_ptr<PhoneType> > &phonesTypes)
{
    beginResetModel();
    
    m_phonesTypes = phonesTypes;
    
    endResetModel();
}

quint64 PhonesTypesModel::getPhoneTypeIdByRow(const int row) const
{
    if (row >= m_phonesTypes.length())
        return 0;
    
    return m_phonesTypes[row]->getTypeId();
}
